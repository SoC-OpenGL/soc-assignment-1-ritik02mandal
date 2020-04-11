#version 400

in vec3 vs_position;

out vec4 frag_colour;

void main () 
{
	
        float r1= 0.6f;
	float r2=0.4f;
        float r=(vs_position.x*vs_position.x) + (vs_position.y*vs_position.y);
        if (r1*r1>=r && r2*r2<=r)
        {
            frag_colour = vec4 (0.5, 1.0, 0.3, 1.0);
        }
        else 
	{
	    frag_colour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
