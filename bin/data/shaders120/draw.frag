#version 120
#extension GL_ARB_texture_rectangle : enable
uniform vec3 mouse;
uniform float time;
uniform sampler2DRect tex0;
varying vec2 uv;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
    vec4 col = texture2DRect(tex0, gl_TexCoord[0].st);
    float avg = dot(col.rgb, vec3(1.0))*0.333;
    if(avg < 0.01){
        discard;
    }
//    float r = rand(gl_TexCoord[0].st);
//    col.rgb *= r;
//    col.r = 1.0 - col.r;
    gl_FragColor = col;//)vec4(mod(time*0.01, 1.0), 1.0, 1.0, 0.1);
}
