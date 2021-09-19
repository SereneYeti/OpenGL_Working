#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

in vec2 TexCoord;

uniform float mixValue;
uniform float mixValue2;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
    //FragColor = texture(texture1, TexCoord);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
    //FragColor = mix(mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue),vec4(lightColor * objectColor, 1.0),mixValue2);
}