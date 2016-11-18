#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect tex0;
uniform float time;
uniform float disp;
varying vec2 uv;
uniform vec2 res;
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    uv = texture2DRect(particles1, gl_TexCoord[0].st).xy;
    vec3 col = texture2DRect(tex0, gl_TexCoord[0].st).xyz;
    float particleZ = col.r;//dot(col.xyz, vec3(1.0))*0.3333;
    
    gl_FrontColor = gl_Color;
    vec4 img =texture2DRect(particles0, gl_TexCoord[0].st);
//    img.y += 60.0;
    vec2 tc = gl_TexCoord[0].xy / res;
//    img.y += sin( tc.x*30.1 + time*0.1)*0.5;
    
//    gl_Position = gl_ModelViewProjectionMatrix * vec4(img.xy * (1.0 + (1.0 - col.r)*2.0), particleZ*disp, 1.0);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(img.xy, particleZ*disp, 1.0);

}
