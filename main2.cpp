
#include <Windows.h>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "tga.h"
#include "program.h"
#include "cube.h"
#include "teapot.h"
#include "openGl.h"


//Macierze
glm::mat4  P;//rzutowania
glm::mat4  V;//widoku
glm::mat4  M;//modelu

//Ustawienia okna i rzutowania
int windowPositionX=100;
int windowPositionY=100;


//Zmienne do animacji
float speed=120; //120 stopni/s
int lastTime=0;
float angle=0;

//Uchwyty na shadery
ShaderProgram *shaderProgram; //Wska�nik na obiekt reprezentuj�cy program cieniuj�cy.

//Uchwyty na VAO i bufory wierzcho�k�w
GLuint vao, vao2, vao3, vao4, vao5;
GLuint bufVertices, bufVertices2, bufVertices3, bufVertices4, bufVertices5; //Uchwyt na bufor VBO przechowuj�cy tablic� wsp�rz�dnych wierzcho�k�w
GLuint bufColors, bufColors2, bufColors3, bufColors4, bufColors5;  //Uchwyt na bufor VBO przechowuj�cy tablic� kolor�w
GLuint bufNormals, bufNormals2, bufNormals3, bufNormals4, bufNormals5; //Uchwyt na bufor VBO przechowuj�cy tablick� wektor�w normalnych

//"Model" kt�ry rysujemy
float *vertices, *vertices2, *vertices3, *vertices4, *vertices5;
float *colors, *colors2, *colors3, *colors4, *colors5;
float *normals, *normals2, *normals3, *normals4, *normals5 ;
int vertexCount, vertexCount2, vertexCount3, vertexCount4, vertexCount5;


//Procedura rysuj�ca jaki� obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
void drawObject() {
	//W��czenie programu cieniuj�cego, kt�ry ma zosta� u�yty do rysowania
	//W tym programie wystarczy�oby wywo�a� to raz, w setupShaders, ale chodzi o pokazanie, 
	//�e mozna zmienia� program cieniuj�cy podczas rysowania jednej sceny

	
	shaderProgram->use();
	
	//Przeka� do shadera macierze P,V i M.
	//W linijkach poni�ej, polecenie:
	//  shaderProgram->getUniformLocation("P") 
	//pobiera numer slotu odpowiadaj�cego zmiennej jednorodnej o podanej nazwie
	//UWAGA! "P" w powy�szym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze, 
	//a P w glm::value_ptr(P) odpowiada deklaracji  "glm::mat4  P;" TYM pliku.
	//Ca�a poni�sza linijka przekazuje do zmiennej jednorodnej P w vertex shaderze dane ze zmiennej P
	//zadeklarowanej globalnie w tym pliku. 
	//Pozosta�e polecenia dzia�aj� podobnie.
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	
	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi�za� slot�w atrybut�w z tablicami z danymi
	glBindVertexArray(vao);
	
	//Narysowanie obiektu
	glDrawArrays(GL_LINES,0,vertexCount);
	
	//gluCylinder(gluNewQuadric(),0.2, 0.2, 0.2, 1, 1);
	
 
	//Posprz�tanie po sobie (niekonieczne w sumie je�eli korzystamy z VAO dla ka�dego rysowanego obiektu)
	glBindVertexArray(0);
	
	M=glm::translate(glm::mat4(1.0f),glm::vec3(0.9f,0.0f,-0.9f));
	M=glm::rotate(M,90.0f,glm::vec3(-0.0f,1.0f,-0.0f));
	M=glm::translate(M,glm::vec3(0.1f,0.0f,0.1f));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	
	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi�za� slot�w atrybut�w z tablicami z danymi
	glBindVertexArray(vao2);

	

	glDrawArrays(GL_TRIANGLES,0,vertexCount2);

	M=glm::translate(M,glm::vec3(0.0f,0.0f,0.2f));
	glDrawArrays(GL_TRIANGLES,0,vertexCount2);

	glBindVertexArray(0);

	//M=glm::translate(M,glm::vec3(0.0f,0.0f,0.2f));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	glBindVertexArray(vao2);

	

	glDrawArrays(GL_TRIANGLES,0,vertexCount2);

	

	glBindVertexArray(0);

	//glBindVertexArray(0);

	M=glm::mat4(1.0f);
	M=glm::rotate(M,90.0f,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(0.1f,0.0f,-0.1f));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	glBindVertexArray(vao3);

	glDrawArrays(GL_TRIANGLES,0,vertexCount3);

	glBindVertexArray(0);

	M=glm::mat4(1.0f);
	M=glm::rotate(M,180.0f,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(-0.5f,0.0f,0.1f));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	glBindVertexArray(vao4);

	glDrawArrays(GL_TRIANGLES,0,vertexCount4);

	glBindVertexArray(0);

	M=glm::mat4(1.0f);
	M=glm::translate(M,glm::vec3(0.5f,0.0f,-0.3f));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(M));
	glBindVertexArray(vao5);

	glDrawArrays(GL_TRIANGLES,0,vertexCount5);

	glBindVertexArray(0);


}

//Procedura rysuj�ca
void displayFrame() {
	//Wyczy�� bufor kolor�w i bufor g��boko�ci
	glClearColor(1.0,0.87,0.68,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Wylicz macierz widoku
	V=glm::lookAt(glm::vec3(0.0f,2.0f,-2.0f),glm::vec3(0.0f,0.0f,-0.0f),glm::vec3(0.0f,1.0f,0.0f)); 

	//Wylicz macierz modelu
	M=glm::mat4(1.0f);//rotate(glm::mat4(1.0f),angle,glm::vec3(0.5,1,0)); 
	
	//Narysuj obiekt
	drawObject();
	
	//Tylny bufor na przedni
	glutSwapBuffers();
}



//Procedura tworz�ca bufory VBO zawieraj�ce dane z tablic opisuj�cych rysowany obiekt.
void setupVBO() {

	//Wyb�r rysowanego modelu (poprzez zakomentowanie/odkomentowanie fragmentu kodu)
	vertices=lines;
	colors=linesColors;
	normals=linesNormal;
	vertexCount=linesCount;


	float clrs[1512];
	float nrmls[1512];
	for(int i=0; i<1344; i+=4){

		if(i%12==0){
			clrs[i]=0.3f; clrs[i+1]=0.8f; clrs[i+2]= 0.2f; clrs[i+3]= 1.0f;

		}

		if(i%12==4){
			clrs[i]=0.0f; clrs[i+1]=0.5f; clrs[i+2]= 0.6f; clrs[i+3]= 1.0f;
			
		}
		if(i%12==8){
			clrs[i]=0.3f; clrs[i+1]=0.9f; clrs[i+2]= 0.4f; clrs[i+3]= 1.0f;

		}
		nrmls[i]=1.0f; nrmls[i+1]=1.0f; nrmls[i+2]=1.0f; nrmls[i+3]=0.0f;
	}

	for(int i=1344;i<1416;i+=4){
		
		nrmls[i]=1.0f; nrmls[i+1]=1.0f; nrmls[i+2]=1.0f; nrmls[i+3]=0.0f;
		clrs[i]=0.0f; clrs[i+1]=0.0f; clrs[i+2]=0.0f; clrs[i+3]=1.0f;//0.74f; clrs[i+1]=0.75f; clrs[i+2]= 0.42f; clrs[i+3]= 1.0f;
		

	}

	for(int i=1416;i<1488;i+=4){
		
		nrmls[i]=1.0f; nrmls[i+1]=1.0f; nrmls[i+2]=1.0f; nrmls[i+3]=0.0f;
		clrs[i]=1.0f; clrs[i+1]=1.0f; clrs[i+2]= 1.0f; clrs[i+3]= 1.0f;
	}

	for(int i=1488;i<1512;i+=4){
		
		nrmls[i]=1.0f; nrmls[i+1]=1.0f; nrmls[i+2]=1.0f; nrmls[i+3]=0.0f;
		clrs[i]=1.0f; clrs[i+1]=0.0f; clrs[i+2]= 0.0f; clrs[i+3]= 0.0f;
	}

	vertices2=snkVertices;
	colors2=clrs;
	normals2=nrmls;
	vertexCount2=336;

	vertices3=snkTail;
	colors3=clrs;
	normals3=nrmls;
	vertexCount3=168;

	vertices4=snkVertices2;
	colors4=clrs;
	normals4=nrmls;
	vertexCount4=336;

	vertices5=snkHead;
	colors5=clrs;
	normals5=nrmls;
	vertexCount5=378;
   /* vertices=teapotVertices;
	colors=teapotColors;
	normals=teapotNormals2;
	vertexCount=teapotVertexCount;*/

	//Wsp�rz�dne wierzcho�k�w
	glGenBuffers(1,&bufVertices);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER,bufVertices);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(float)*4, vertices, GL_STATIC_DRAW); //wgraj tablic� wierzcho�k�w do VBO
	
	//Kolory wierzcho�k�w
	glGenBuffers(1,&bufColors);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� kolor�w
	glBindBuffer(GL_ARRAY_BUFFER,bufColors);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(float)*4, colors, GL_STATIC_DRAW); //wgraj tablic� kolor�w do VBO
	
	//Wektory normalne wierzcho�k�w
	glGenBuffers(1,&bufNormals);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wektor�w normalnych
	glBindBuffer(GL_ARRAY_BUFFER,bufNormals);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(float)*4, normals, GL_STATIC_DRAW); //wgraj tablic� wektor�w normalnych do VBO
	
	glGenBuffers(1,&bufVertices2);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER,bufVertices2);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount2*sizeof(float)*4, vertices2, GL_STATIC_DRAW); //wgraj tablic� wierzcho�k�w do VBO
	
	//Kolory wierzcho�k�w
	glGenBuffers(1,&bufColors2);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� kolor�w
	glBindBuffer(GL_ARRAY_BUFFER,bufColors2);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount2*sizeof(float)*4, colors2, GL_STATIC_DRAW); //wgraj tablic� kolor�w do VBO
	
	//Wektory normalne wierzcho�k�w
	glGenBuffers(1,&bufNormals2);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wektor�w normalnych
	glBindBuffer(GL_ARRAY_BUFFER,bufNormals2);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount2*sizeof(float)*4, normals2, GL_STATIC_DRAW); //wgraj tablic� wektor�w normalnych do VBO

	glGenBuffers(1,&bufVertices3);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER,bufVertices3);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount3*sizeof(float)*4, vertices3, GL_STATIC_DRAW); //wgraj tablic� wierzcho�k�w do VBO
	
	//Kolory wierzcho�k�w
	glGenBuffers(1,&bufColors3);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� kolor�w
	glBindBuffer(GL_ARRAY_BUFFER,bufColors3);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount3*sizeof(float)*4, colors3, GL_STATIC_DRAW); //wgraj tablic� kolor�w do VBO
	
	//Wektory normalne wierzcho�k�w
	glGenBuffers(1,&bufNormals3);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wektor�w normalnych
	glBindBuffer(GL_ARRAY_BUFFER,bufNormals3);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount3*sizeof(float)*4, normals3, GL_STATIC_DRAW); //wgraj tablic� wektor�w normalnych do VBO

	glGenBuffers(1,&bufVertices4);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER,bufVertices4);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount4*sizeof(float)*4, vertices4, GL_STATIC_DRAW); //wgraj tablic� wierzcho�k�w do VBO
	
	//Kolory wierzcho�k�w
	glGenBuffers(1,&bufColors4);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� kolor�w
	glBindBuffer(GL_ARRAY_BUFFER,bufColors4);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount4*sizeof(float)*4, colors4, GL_STATIC_DRAW); //wgraj tablic� kolor�w do VBO
	
	//Wektory normalne wierzcho�k�w
	glGenBuffers(1,&bufNormals4);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wektor�w normalnych
	glBindBuffer(GL_ARRAY_BUFFER,bufNormals4);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount4*sizeof(float)*4, normals4, GL_STATIC_DRAW); //wgraj tablic� wektor�w normalnych do VBO

	glGenBuffers(1,&bufVertices5);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER,bufVertices5);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount5*sizeof(float)*4, vertices5, GL_STATIC_DRAW); //wgraj tablic� wierzcho�k�w do VBO
	
	//Kolory wierzcho�k�w
	glGenBuffers(1,&bufColors5);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� kolor�w
	glBindBuffer(GL_ARRAY_BUFFER,bufColors5);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount5*sizeof(float)*4, colors5, GL_STATIC_DRAW); //wgraj tablic� kolor�w do VBO
	
	//Wektory normalne wierzcho�k�w
	glGenBuffers(1,&bufNormals5);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), kt�ry b�dzie zawiera� tablic� wektor�w normalnych
	glBindBuffer(GL_ARRAY_BUFFER,bufNormals5);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount5*sizeof(float)*4, normals5, GL_STATIC_DRAW); //wgraj tablic� wektor�w normalnych do VBO
	
}
//Procedura tworz�ca VAO - "obiekt" OpenGL wi���cy numery slot�w atrybut�w z buforami VBO
void setupVAO() {
	//Pobierz numery slot�w poszczeg�lnych atrybut�w
	GLuint locVertex=shaderProgram->getAttribLocation("vertex"); //"vertex" odnosi si� do deklaracji "in vec4 vertex;" w vertex shaderze
	GLuint locColor=shaderProgram->getAttribLocation("color"); //"color" odnosi si� do deklaracji "in vec4 color;" w vertex shaderze
	GLuint locNormal=shaderProgram->getAttribLocation("normal"); //"normal" odnosi si� do deklaracji "in vec4 normal;" w vertex shaderze

	//Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej
	glGenVertexArrays(1,&vao);
	glGenVertexArrays(1,&vao2);
	glGenVertexArrays(1,&vao3);
	glGenVertexArrays(1,&vao4);
	glGenVertexArrays(1,&vao5);

	//Uaktywnij nowo utworzony VAO
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,bufVertices);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locVertex); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
	glVertexAttribPointer(locVertex,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj� by� brane z aktywnego VBO
	
	glBindBuffer(GL_ARRAY_BUFFER,bufColors);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locColor); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locColor (atrybut "color")
	glVertexAttribPointer(locColor,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locColor maj� by� brane z aktywnego VBO

	glBindBuffer(GL_ARRAY_BUFFER,bufNormals);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locNormal); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
	glVertexAttribPointer(locNormal,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj� by� brane z aktywnego VBO

	glBindVertexArray(0);

	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER,bufVertices2);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locVertex); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
	glVertexAttribPointer(locVertex,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj� by� brane z aktywnego VBO
	
	glBindBuffer(GL_ARRAY_BUFFER,bufColors2);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locColor); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locColor (atrybut "color")
	glVertexAttribPointer(locColor,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locColor maj� by� brane z aktywnego VBO

	glBindBuffer(GL_ARRAY_BUFFER,bufNormals2);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locNormal); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
	glVertexAttribPointer(locNormal,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj� by� brane z aktywnego VBO

	glBindVertexArray(0);
	
	glBindVertexArray(vao3);

	glBindBuffer(GL_ARRAY_BUFFER,bufVertices3);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locVertex); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
	glVertexAttribPointer(locVertex,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj� by� brane z aktywnego VBO
	
	glBindBuffer(GL_ARRAY_BUFFER,bufColors3);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locColor); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locColor (atrybut "color")
	glVertexAttribPointer(locColor,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locColor maj� by� brane z aktywnego VBO

	glBindBuffer(GL_ARRAY_BUFFER,bufNormals3);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locNormal); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
	glVertexAttribPointer(locNormal,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj� by� brane z aktywnego VBO

	glBindVertexArray(0);

	glBindVertexArray(vao4);

	glBindBuffer(GL_ARRAY_BUFFER,bufVertices4);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locVertex); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
	glVertexAttribPointer(locVertex,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj� by� brane z aktywnego VBO
	
	glBindBuffer(GL_ARRAY_BUFFER,bufColors4);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locColor); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locColor (atrybut "color")
	glVertexAttribPointer(locColor,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locColor maj� by� brane z aktywnego VBO

	glBindBuffer(GL_ARRAY_BUFFER,bufNormals4);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locNormal); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
	glVertexAttribPointer(locNormal,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj� by� brane z aktywnego VBO

	glBindVertexArray(0);

	glBindVertexArray(vao5);

	glBindBuffer(GL_ARRAY_BUFFER,bufVertices5);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locVertex); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
	glVertexAttribPointer(locVertex,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj� by� brane z aktywnego VBO
	
	glBindBuffer(GL_ARRAY_BUFFER,bufColors5);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locColor); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locColor (atrybut "color")
	glVertexAttribPointer(locColor,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locColor maj� by� brane z aktywnego VBO

	glBindBuffer(GL_ARRAY_BUFFER,bufNormals5);  //Uaktywnij wygenerowany uchwyt VBO 
	glEnableVertexAttribArray(locNormal); //W��cz u�ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
	glVertexAttribPointer(locNormal,4,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj� by� brane z aktywnego VBO

	glBindVertexArray(0);
	
}


//Procedura definiuj�ca macierz rzutowania
void setupProjection(float angle,int w, int h) {
	P=glm::perspective(angle, (float)w/(float)h, 1.0f, 100.0f);
}

//Procedura uruchamiana okresowo. Robi animacj�.
void nextFrame(void) {
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	//angle+=speed*interval/1000.0;
	//if (angle>360) angle-=360;
	glutPostRedisplay();
}

//Procedura wywo�ywana przy zmianie rozmiaru okna
void changeSize(int w, int h) {
	//Ustawienie wymiarow przestrzeni okna
	glViewport(0,0,w,h);
	//Dostosowanie macierzy rzutowania do nowego wymiaru okna
	setupProjection(cameraAngle,w,h);
}

//Procedura inicjuj�ca biblotek� glut
void initGLUT(int *argc, char** argv) {
	glutInit(argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowPosition(windowPositionX,windowPositionY);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Snake3D");
	
	glutReshapeFunc(changeSize); //Procedura obs�uguj�ca zmian� rozmiaru okna
	glutDisplayFunc(displayFrame); //Procedura obs�uguj�ca od�wierzanie okna
	glutIdleFunc(nextFrame); //Procedura wywo�uj�ca najcz�ciaj jak si� da (animacja)
}


//Procedura inicjuj�ca bibliotek� glew
void initGLEW() {
	GLenum err=glewInit();
	if (GLEW_OK!=err) {
		fprintf(stderr,"%s\n",glewGetErrorString(err));
		exit(1);
	}
	
}



//Wczytuje vertex shader i fragment shader i ��czy je w program cieniuj�cy
void setupShaders() {
	shaderProgram=new ShaderProgram("vshader.txt",NULL,"fshader.txt");
}

//procedura inicjuj�ca r�ne sprawy zwi�zane z rysowaniem w OpenGL
void initOpenGL(float angle,int w,int h) {
	setupProjection(angle,w,h);
	setupShaders();
	setupVBO();
	setupVAO();
	glEnable(GL_DEPTH_TEST);
}

//Zwolnij pami�� karty graficznej z shader�w i programu cieniuj�cego
void cleanShaders() {
	delete shaderProgram;
}

void freeVBO() {
	glDeleteBuffers(1,&bufVertices);
	glDeleteBuffers(1,&bufColors);
	glDeleteBuffers(1,&bufNormals);
}

void freeVAO() {
	glDeleteVertexArrays(1,&vao);
}


/*int main(int argc, char** argv) {
	initGLUT(&argc,argv);
	initGLEW();
	initOpenGL(cameraAngle,windowWidth,windowHeight);
	
	glutMainLoop();
	
	freeVAO();
	freeVBO();
	cleanShaders();
	return 0;
}*/
