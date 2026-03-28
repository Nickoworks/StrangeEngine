#version 330 core

uniform vec2 resolution;
uniform vec2 sdlCoords;
uniform float intencity;
uniform float centralOpacity;
uniform float size;
uniform vec4 startColor;
uniform vec4 glowColor;
uniform int shapeType;
uniform vec2 shapeTransform;
uniform float distance;
uniform vec2 lightDir;

out vec4 FragColor;

void main() {
    vec2 coords;

    coords.x = ((2.0 * (sdlCoords.x / resolution.x)) - 1.0) * ((resolution.x / resolution.y) / 2.0);
    coords.y = (1.0 - (2.0 * (sdlCoords.y / resolution.y))) / 2.0;

    float size_ = size / 100.0;
    float distance_ = distance; 

    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;


    vec2 UV = (uv - coords) / shapeTransform;
    float dist = 1.0;

    switch(shapeType){
        case 0:
            dist = length(UV);
            break;
        case 1:
            dist = max(abs(UV.x), abs(UV.y));
            break;        
    }

    vec2 lightToFrag = normalize(UV);
    float dirFactor = max(dot(lightToFrag, normalize(lightDir)), 0.0);

    vec4 centerColor = startColor; 
    vec4 edgeColor = glowColor;
    vec4 col = mix(centerColor, edgeColor, smoothstep(0.0, size_, dist));

    float glow = size_ / (dist + 0.1); 
    col += glow * glowColor * centerColor;

    float alpha;
    if(lightDir == vec2(0.0, 0.0)){
        alpha = intencity * exp(-dist * distance);
    } else {
        alpha = intencity * exp(-dist * distance) * dirFactor;
    }

    float centralEffect = mix(centralOpacity, alpha, smoothstep(0.0, size_, dist));
    alpha = clamp(centralEffect, 0.0, intencity);

    col.a = alpha;

    FragColor = col;
}
