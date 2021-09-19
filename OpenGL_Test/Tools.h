#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
namespace Tool
{
	class Tools
	{
	public:
		enum ToolSelect
		{
			Rot, Trans, Scale,
			Rot_Trans, Rot_Scale,
			Trans_Scale, Trans_Rot,
			Scale_Rot, Scale_Trans,
			Rot_Trans_Scale, Trans_Rot_Scale,
			Trans_Scale_Rot, Scale_Rot_Trans
		};
		Tools();
		~Tools();
		//Rotates Scales or Transofmrs an object based on arguments given
		void Rotate_Transform_Scale_Object(glm::mat4 model, ToolSelect tool, glm::vec3 rot,float angle, glm::vec3 trans, glm::vec3 scale);		

	private:
		float test = 0.2f;
	};
}
