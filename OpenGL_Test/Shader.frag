#version 330 core
out vec4 FragColor;

in vec3 ourColor; //Takes a colour from the vert shader.
in vec3 ourPosition; //Takes a position for use as a colour from the vert shader.




void main()
{
    FragColor = vec4(ourColor, 1.0);
    //FragColor = vec4(ourPosition, 1.0);   
}


