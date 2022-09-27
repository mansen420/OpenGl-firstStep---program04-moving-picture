#version 330 core
out vec4 fragColor;

in vec2 textPass;
in vec3 positionPass;
in vec3 colorPass;

uniform float mix_setting = 0;
uniform sampler2D texture02;
uniform sampler2D texture01;
void main(){
	fragColor = mix(texture( texture01 , textPass ), texture(texture02,vec2(1.0-textPass.x,textPass.y)),mix_setting)  +  -0.4*mix_setting*vec4(colorPass,1.0) +
	-(1-mix_setting)*vec4(0.6,0.6,0.5,1.0);
}