#version 330 core 
bool reachedEdge(vec2 coords);
bool reachedLeftEdge(vec2 coords);
bool reachedRightEdge(vec2 coords);

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textCoords;
layout (location = 2) in vec3 aColor;

out vec3 colorPass;
out vec3 positionPass;
out vec2 textPass;


uniform float vertical=0;
uniform float horizontal=0; 
void main (){
	gl_Position= vec4(aPos.x , aPos.y,aPos.z,1.0);
	textPass= textCoords;
	positionPass=aPos;
	colorPass=aColor;
}