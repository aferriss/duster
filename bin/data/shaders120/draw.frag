#version 120
#extension GL_ARB_texture_rectangle : enable
uniform vec3 mouse;
uniform float time;
uniform sampler2DRect tex0;
varying vec2 uv;

void main(){
    vec4 col = texture2DRect(tex0, gl_TexCoord[0].st);
    float avg = dot(col.rgb, vec3(1.0))*0.333;
    if(avg < 0.1){
        discard;
    }
    gl_FragColor = col;//)vec4(mod(time*0.01, 1.0), 1.0, 1.0, 0.1);
}
