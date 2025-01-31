#include "raylib.h"
#include <vector>
#include <string>
#include <string.h>
#include<stdio.h>
#include<iostream>
#include <fstream>
#include <pugixml.hpp>

#define HEIGHT_BEDROOM 500
#define WEIGHT_BEDROOM 400
#define HEIGHT_REDACTOR 500
#define WEIGHT_REDACTOR 500
static bool pressed = false;
static int id;
class redactor {
private:

	int x = 700;
	int y = 20;
public:

	void drawing() {
		DrawRectangle(x, y, WEIGHT_REDACTOR, HEIGHT_REDACTOR, LIGHTGRAY);
		DrawText("EDITOR", x + 50, y + 20, 40, BLACK);
		DrawText("BED", 830, 106, 40, BLACK);
		DrawText("CHEST", 830, 176, 40, BLACK);
		DrawText("TABLE", 830, 246, 40, BLACK);
		DrawText("CHAIR", 830, 316, 40, BLACK);
		DrawText("SOFA", 830, 386, 40, BLACK);
	}
};
class room {
private:

	int x = 20;// координаты с которых начинается рисунок
	int y = 20;
public:
	int get_x() {
		return x;
	}
	int get_y() {
		return y;
	}

	void drawing() {
		DrawRectangle(x, y, WEIGHT_BEDROOM, HEIGHT_BEDROOM, LIGHTGRAY);
	}
};
class button {
private:
	int touch_x;
	int touch_y;
	Texture2D object = LoadTexture("plus.png");
public:
	button(int x, int y) {
		touch_x = x;
		touch_y = y;
	}
	Texture2D get_b() {
		return object;
	}
	int get_x() {
		return touch_x;
	}
	int get_y() {
		return touch_y;
	}
	void drawing() {
		DrawTexture(object, touch_x, touch_y, WHITE);
	}
};
class button_save {
private:
	int touch_x;
	int touch_y;
	Texture2D object = LoadTexture("save.png");
public:
	button_save(int x, int y) {
		touch_x = x;
		touch_y = y;
	}
	Texture2D get_b() {
		return object;
	}
	int get_x() {
		return touch_x;
	}
	int get_y() {
		return touch_y;
	}
	void drawing() {
		DrawTexture(object, touch_x, touch_y, WHITE);
	}
};
class button_load {
private:
	int touch_x;
	int touch_y;
	Texture2D object = LoadTexture("load.png");
public:
	button_load(int x, int y) {
		touch_x = x;
		touch_y = y;
	}
	Texture2D get_b() {
		return object;
	}
	int get_x() {
		return touch_x;
	}
	int get_y() {
		return touch_y;
	}
	void drawing() {
		DrawTexture(object, touch_x, touch_y, WHITE);
	}
};
class item {
public:
	virtual void drawing() = 0;
	virtual int get_x() = 0;
	virtual void set_x(int x) = 0;
	virtual int get_y() = 0;
	virtual void set_y(int y) = 0;
	virtual Texture2D get_texture() = 0;
	virtual void set_rot(float a) = 0;
	virtual float get_rot() = 0;
	virtual std::string get_string() = 0;

};
class bed :public item {
private:
	float rot = 0;
	std::string s = "bed";
	Texture2D object;
	Vector2 pos;
public:
	Texture2D get_texture() {
		return object;
	}
	bed() { object = LoadTexture("Bed.png"); }
	bed(int a, int b) {

		object = LoadTexture("Bed.png");
		this->pos.x = a;
		this->pos.y = b;
	}
	std::string get_string() {
		return s;
	}
	int get_x() {
		return pos.x;
	}
	void set_rot(float a) {
		this->rot = this->rot + a;


	}
	float get_rot() {
		return rot;
	}
	int get_y() {
		return pos.y;
	}
	void set_x(int x) {
		this->pos.x = x;

	}
	void set_y(int y) {
		this->pos.y = y;
	}
	void drawing() {
		DrawTextureEx(object, pos, rot, 1, WHITE);
	}
	~bed() {
		UnloadTexture(object);
	}
};
class chest :public item {
private:
	float rot = 0;
	std::string s = "chest";
	Texture2D object;
	Vector2 pos;
public:
	Texture2D get_texture() {
		return object;
	}
	chest() { object = LoadTexture("shkaf.png"); }
	chest(int a, int b) {

		object = LoadTexture("shkaf.png");
		this->pos.x = a;
		this->pos.y = b;
	}
	std::string get_string() {
		return s;
	}
	int get_x() {
		return pos.x;
	}
	void set_rot(float a) {
		this->rot = this->rot + a;


	}
	float get_rot() {
		return rot;
	}
	int get_y() {
		return pos.y;
	}
	void set_x(int x) {
		this->pos.x = x;

	}
	void set_y(int y) {
		this->pos.y = y;
	}
	void drawing() {
		DrawTextureEx(object, pos, rot, 1, WHITE);
	}
	~chest() {
		UnloadTexture(object);
	}
};
class table :public item {
private:
	float rot = 0;
	std::string s = "table";
	Texture2D object;
	Vector2 pos;
public:
	Texture2D get_texture() {
		return object;
	}
	table() { object = LoadTexture("table.png"); }
	table(int a, int b) {

		object = LoadTexture("table.png");
		this->pos.x = a;
		this->pos.y = b;
	}
	std::string get_string() {
		return s;
	}
	int get_x() {
		return pos.x;
	}
	void set_rot(float a) {
		this->rot = this->rot + a;
		;

	}
	float get_rot() {
		return rot;
	}
	int get_y() {
		return pos.y;
	}
	void set_x(int x) {
		this->pos.x = x;

	}
	void set_y(int y) {
		this->pos.y = y;
	}
	void drawing() {
		DrawTextureEx(object, pos, rot, 1, WHITE);
	}
	~table() {
		UnloadTexture(object);
	}
};
class chair :public item {
private:
	float rot = 0;
	std::string s = "chair";
	Texture2D object;
	Vector2 pos;
public:
	Texture2D get_texture() {
		return object;
	}
	chair() { object = LoadTexture("chair.png"); }
	chair(int a, int b) {

		object = LoadTexture("chair.png");
		this->pos.x = a;
		this->pos.y = b;
	}
	std::string get_string() {
		return s;
	}
	int get_x() {
		return pos.x;
	}
	void set_rot(float a) {
		this->rot = this->rot + a;


	}
	float get_rot() {
		return rot;
	}
	int get_y() {
		return pos.y;
	}
	void set_x(int x) {
		this->pos.x = x;

	}
	void set_y(int y) {
		this->pos.y = y;
	}
	void drawing() {
		DrawTextureEx(object, pos, rot, 1, WHITE);
	}
	~chair() {
		UnloadTexture(object);
	}
};
class sofa :public item {
private:
	float rot = 0;
	std::string s = "sofa";
	Texture2D object;
	Vector2 pos;
public:
	Texture2D get_texture() {
		return object;
	}
	sofa() { object = LoadTexture("sofa.png"); }
	sofa(int a, int b) {

		object = LoadTexture("sofa.png");
		this->pos.x = a;
		this->pos.y = b;
	}

	int get_x() {
		return pos.x;
	}
	void set_rot(float a) {
		this->rot = this->rot + a;


	}
	float get_rot() {
		return rot;
	}
	int get_y() {
		return pos.y;
	}
	void set_x(int x) {
		this->pos.x = x;

	}
	std::string get_string() {
		return s;
	}
	void set_y(int y) {
		this->pos.y = y;
	}
	void drawing() {
		DrawTextureEx(object, pos, rot, 1, WHITE);
	}
	~sofa() {
		UnloadTexture(object);
	}
};
void Initbutton(std::vector<button>* allbutton) {
	button bbet(750, 100);
	(*allbutton).push_back(bbet);// кидаем в вектор класс кнопки 
	button bchest(750, 170);
	(*allbutton).push_back(bchest);
	button btable(750, 240);
	(*allbutton).push_back(btable);
	button bchair(750, 310);
	(*allbutton).push_back(bchair);
	button bsofa(750, 380);
	(*allbutton).push_back(bsofa);


}
void add_bed(std::vector<item*>* create_object) {
	bed* object = new bed(150, 150);
	(*create_object).push_back(object);
}
void add_chest(std::vector<item*>* create_object) {
	chest* object = new chest(150, 150);
	(*create_object).push_back(object);
}
void add_table(std::vector<item*>* create_object) {
	table* object = new table(150, 150);
	(*create_object).push_back(object);
}
void add_chair(std::vector<item*>* create_object) {
	chair* object = new chair(150, 150);
	(*create_object).push_back(object);
}
void add_sofa(std::vector<item*>* create_object) {
	sofa* object = new sofa(150, 150);
	(*create_object).push_back(object);
}
int main() {
	std::fstream fs;
	std::vector<item*> create_object;/// массив хранит указатели на классы
	std::vector<button> all_button;
	InitWindow(1280, 800, "IDZ Matveychev IV 8 variant");
	room bedroom;
	redactor shop;
	Initbutton(&all_button);
	button_save bsave(1100, 470);
	button_load bload(1150, 465);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		shop.drawing();
		bedroom.drawing();
		for (int i = 0; i < all_button.size(); ++i) {
			all_button[i].drawing();
		}
		for (int i = 0; i < all_button.size(); ++i) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ((GetMousePosition().x >= all_button[i].get_x()) && (GetMousePosition().x <= (all_button[i].get_x() + all_button[i].get_b().width)) && (GetMousePosition().y >= all_button[i].get_y()) && (GetMousePosition().y <= all_button[i].get_y() + all_button[i].get_b().height)))
			{
				if (i == 0)
					add_bed(&create_object);
				if (i == 1)
					add_chest(&create_object);
				if (i == 2)
					add_table(&create_object);
				if (i == 3)
					add_chair(&create_object);
				if (i == 4)
					add_sofa(&create_object);

			}
		}
		bsave.drawing();
		bload.drawing();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ((GetMousePosition().x >= bsave.get_x()) && (GetMousePosition().x <= (bsave.get_x() + bsave.get_b().width)) && (GetMousePosition().y >= bsave.get_y()) && (GetMousePosition().y <= bsave.get_y() + bsave.get_b().height)))
		{
			fs.open("C:\Users\ванёк\source\repos\IDZ_VANEK_8VAR\IDZ_VANEK_8VAR\file.xml", std::ifstream::in | std::ifstream::out);
			if (!fs.is_open()) {
				std::cout << "oshibka :/" << std::endl;
			}
			else {

				for (int i = 0; i < create_object.size(); ++i) {
					fs << (*create_object[i]).get_string() << "\n";
					fs << (*create_object[i]).get_x() << "\n";
					fs << (*create_object[i]).get_y() << "\n";
					fs << (*create_object[i]).get_rot() << "\n";

				}
			}
			fs.close();
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ((GetMousePosition().x >= bload.get_x()) && (GetMousePosition().x <= (bload.get_x() + bload.get_b().width)) && (GetMousePosition().y >= bload.get_y()) && (GetMousePosition().y <= bload.get_y() + bload.get_b().height)))
		{
			create_object.clear();
			fs.open("C:\Users\ванёк\source\repos\IDZ_VANEK_8VAR\IDZ_VANEK_8VAR\file.xml", std::ifstream::in | std::ifstream::out);
			if (!fs.is_open()) {
				std::cout << "oshibka :/" << std::endl;
			}
			else {
				std::cout << "vse xorosho" << std::endl;
				while (!fs.eof()) {
					std::string tmp;
					fs >> tmp;
					if (tmp == "bed") {
						bed* object = new bed();
						int tmp_s;
						fs >> tmp_s;
						object->set_x(tmp_s);
						fs >> tmp_s;
						object->set_y(tmp_s);
						fs >> tmp_s;
						object->set_rot(tmp_s);
						create_object.push_back(object);
					}
					if (tmp == "chest") {
						chest* object = new chest();
						int tmp_s;
						fs >> tmp_s;
						object->set_x(tmp_s);
						fs >> tmp_s;
						object->set_y(tmp_s);
						fs >> tmp_s;
						object->set_rot(tmp_s);
						create_object.push_back(object);
					}
					if (tmp == "table") {
						table* object = new table();
						int tmp_s;
						fs >> tmp_s;
						object->set_x(tmp_s);
						fs >> tmp_s;
						object->set_y(tmp_s);
						fs >> tmp_s;
						object->set_rot(tmp_s);
						create_object.push_back(object);
					}
					if (tmp == "chair") {
						chair* object = new chair();
						int tmp_s;
						fs >> tmp_s;
						object->set_x(tmp_s);
						fs >> tmp_s;
						object->set_y(tmp_s);
						fs >> tmp_s;
						object->set_rot(tmp_s);
						create_object.push_back(object);
					}
					if (tmp == "sofa") {
						sofa* object = new sofa();
						int tmp_s;
						fs >> tmp_s;
						object->set_x(tmp_s);
						fs >> tmp_s;
						object->set_y(tmp_s);
						fs >> tmp_s;
						object->set_rot(tmp_s);
						create_object.push_back(object);
					}
				}
			}
			fs.close();
		}

		for (int i = 0; i < create_object.size(); ++i) {
			(*create_object[i]).drawing();
		}
		for (int i = 0; i < create_object.size(); ++i) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && (GetMousePosition().x >= (*create_object[i]).get_x()) && (GetMousePosition().x <= ((*create_object[i]).get_x() + (*create_object[i]).get_texture().width)) && (GetMousePosition().y >= (*create_object[i]).get_y()) && (GetMousePosition().y <= (*create_object[i]).get_y() + (*create_object[i]).get_texture().height)) {
				auto idi = create_object.begin();
				item* tmp = create_object[i];
				create_object.erase(idi + i);
				delete tmp;
			}
		}


		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (create_object.size() != 0)) {
			pressed = false;
		}
		else {
			for (int i = 0; i < create_object.size(); ++i) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMousePosition().x >= (*create_object[i]).get_x()) && (GetMousePosition().x <= ((*create_object[i]).get_x() + (*create_object[i]).get_texture().width)) && (GetMousePosition().y >= (*create_object[i]).get_y()) && (GetMousePosition().y <= (*create_object[i]).get_y() + (*create_object[i]).get_texture().height)) {
					id = i;
				}
				else {
					if (create_object.size() == 1)
						id = 0;
				}
			}
			if ((pressed || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMousePosition().x >= (*create_object[id]).get_x()) && (GetMousePosition().x <= ((*create_object[id]).get_x() + (*create_object[id]).get_texture().width)) && (GetMousePosition().y >= (*create_object[id]).get_y()) && (GetMousePosition().y <= (*create_object[id]).get_y() + (*create_object[id]).get_texture().height)))) {
				(*create_object[id]).set_x(GetMouseX());
				(*create_object[id]).set_y(GetMouseY());
				if (IsKeyPressed(KEY_LEFT_CONTROL)) {
					if ((*create_object[id]).get_rot() != 270)
						(*create_object[id]).set_rot(90);
					else
						(*create_object[id]).set_rot(-360);
				}
				pressed = true;
			}
		}

		EndDrawing();
	}
	CloseWindow();

	return 0;
}
