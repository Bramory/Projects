#include <GL/glut.h>

float angle = 0.0f;

void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	// очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнуление трансформации
	glLoadIdentity();
	// установка камеры
	gluLookAt( 0.0f, 0.0f, 10.0f,
		   0.0f, 0.0f,  0.0f,
		   0.0f, 1.0f,  0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 0.0f, 2.0f, 0.0);
		glVertex3f( 2.0f,-2.0f, 0.0);
	glEnd();

	angle+=0.2f;

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	// Инициализация GLUT и создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Perspective");

	// регистрация
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// основной цикл
	glutMainLoop();

	return 0;
}
