#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect tex0;
uniform float disp;
varying vec2 uv;
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    uv = texture2DRect(particles1, gl_TexCoord[0].st).xy;
    vec3 col = texture2DRect(tex0, gl_TexCoord[0].st).xyz;
    float particleZ = dot(col.xyz, vec3(1.0))*0.3333;
    
    gl_FrontColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(texture2DRect(particles0, gl_TexCoord[0].st).xy, particleZ*disp, 1.0);
}
