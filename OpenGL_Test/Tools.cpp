#include "Tools.h"
#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

using namespace Tool;
using namespace std;
//Rotates Scales or Transofmrs an object based on arguments given
void Tools::Rotate_Transform_Scale_Object(glm::mat4 model, ToolSelect tool, glm::vec3 rot, float angle, glm::vec3 trans, glm::vec3 scale) {
	switch(tool) {
		case(Tools::Rot):
		{
			model = glm::rotate(model, glm::radians(angle), rot);
			break;
		}
		case(Tools::Trans):
		{
			cout << "working!";
			model = glm::translate(model, trans);
			break;
		}
		case(Tools::Scale):
		{
			model = glm::scale(model, scale);
			break;
		}
		case(Tools::Rot_Scale):
		{
			model = glm::rotate(model, glm::radians(angle), rot);
			model = glm::scale(model, scale);
			break;
		}
		case(Tools::Scale_Rot):
		{
			model = glm::scale(model, scale);
			model = glm::rotate(model, glm::radians(angle), rot);			
			break;
		}
		case(Tools::Rot_Trans):
		{
			model = glm::rotate(model, glm::radians(angle), rot);
			model = glm::translate(model, trans);
			break;
		}
		case(Tools::Trans_Rot):
		{
			model = glm::translate(model, trans);
			model = glm::rotate(model, glm::radians(angle), rot);			
			break;
		}
		case(Tools::Trans_Scale):
		{
			model = glm::translate(model, trans);
			model = glm::scale(model, scale);
			break;
		}
		case(Tools::Scale_Trans):
		{
			model = glm::scale(model, scale);
			model = glm::translate(model, trans);			
			break;
		}
		case(Tools::Rot_Trans_Scale):
		{
			model = glm::rotate(model, glm::radians(angle), rot);
			model = glm::translate(model, trans);
			model = glm::scale(model, scale);
			break;
		}
		case(Tools::Trans_Rot_Scale):
		{
			model = glm::translate(model, trans);
			model = glm::rotate(model, glm::radians(angle), rot);			
			model = glm::scale(model, scale);
			break;
		}
		case(Tools::Trans_Scale_Rot):
		{
			model = glm::translate(model, trans);
			model = glm::scale(model, scale);
			model = glm::rotate(model, glm::radians(angle), rot);		
			break;
		}
		case(Tools::Scale_Rot_Trans):
		{
			model = glm::scale(model, scale);
			model = glm::rotate(model, glm::radians(angle), rot);
			model = glm::translate(model, trans);			
			break;
		}
	}
}
//Constructor
Tools::Tools() {
	//cout << "Tool Test" << ": " << Tools::test << "!";
}
//Destructor
Tools::~Tools() {

}