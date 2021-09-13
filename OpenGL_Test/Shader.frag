#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 ourPosition;
in float ourTime;
in float ourTracker;

vec3 Test(vec3 vect,float f)
{
    vec3 ans;
    
    
    if(ourTracker <= 4 )
    {   
        ans = vect*f;       
    }
    else if(ourTracker >= 5 )
    {
        ans = vect/f;       
    }
    

    return ans;
}

void main()
{
    FragColor = vec4(ourColor, 1.0);
    //FragColor = vec4(ourPosition, 1.0);    
    //FragColor = vec4(Test(ourColor,ourTime),1.0);    
}


