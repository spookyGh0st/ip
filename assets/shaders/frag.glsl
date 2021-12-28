#version 460 core
#define OPCODE_PLUS 0
#define OPCODE_MINUS 1
#define OPCODE_MULTIPLY 2
#define OPCODE_DIVIDE 3
#define OPCODE_POW 4
#define OPCODE_MODULO 5
#define OPCODE_MAXIMAL 6
#define OPCODE_MINIMAL 7
#define OPCODE_X 8
#define OPCODE_Y 9
#define OPCODE_Z 10
#define OPCODE_SQRT 11
#define OPCODE_FLOAT 12

#define MAX_STEPS 100
#define SURFACE_DIST 0.01
#define MAX_DIST 100 // avoid stepping into infinity

out vec4 color;
uniform usamplerBuffer tapeSampler;
uniform uint tapeSize;
uniform samplerBuffer ramSampler;
uniform uint ramSize;
uniform vec2 iResolution;
uniform float pulseL;
uniform float pulseR;

float ram[2^8];

void emulateClause(in uvec4 clause, in vec3 p) {
    switch (clause.r) {
        case OPCODE_PLUS:
            ram[clause.g] = ram[clause.b] + ram[clause.a];
            break;
        case OPCODE_MINUS:
            ram[clause.g] = ram[clause.b] - ram[clause.a];
            break;
        case OPCODE_MULTIPLY:
            ram[clause.g] = ram[clause.b] * ram[clause.a];
            break;
        case OPCODE_DIVIDE:
            ram[clause.g] = ram[clause.b] / ram[clause.a];
            break;
        case OPCODE_POW:
            ram[clause.g] = pow(ram[clause.b], ram[clause.a]); // todo for loop
            break;
        case OPCODE_MODULO:
            ram[clause.g] = mod(ram[clause.b], ram[clause.a]);
            break;
        case OPCODE_MAXIMAL:
            ram[clause.g] = max(ram[clause.b] , ram[clause.a]);
            break;
        case OPCODE_MINIMAL:
            ram[clause.g] = min(ram[clause.b] , ram[clause.a]);
            break;
        case OPCODE_X:
            ram[clause.g] = p.x;
            break;
        case OPCODE_Y:
            ram[clause.g] = p.y;
            break;
        case OPCODE_Z:
            ram[clause.g] = p.z;
            break;
        case OPCODE_SQRT:
            ram[clause.g] = sqrt(ram[clause.b]);
            break;
        case OPCODE_FLOAT:
            ram[clause.g] = texelFetch(ramSampler,int(clause.b)).r;
            break;
    }
}

float sceneDistanceCapsule(in vec3 p, in vec3 startSphere, in vec3 endSphere, float radius){
    vec3 capsLength =  endSphere - startSphere;
    vec3 pointLength = p - startSphere;

    float t = dot(capsLength, pointLength) / dot(capsLength, capsLength);
    t = clamp(t,0,1);
    vec3 c = startSphere+t*capsLength;
    float d = length(p-c) - radius;
    return d;
}
float sphereDistance(in vec3 p, in vec3 position, in float radius){
    return length(p-position)-radius;
}


float sceneDistance(in vec3 p){
    // int i = 0;
    // for(; i < tapeSize; ++i) {
    //     uvec4 clause = texelFetch(tapeSampler, i);
    //     emulateClause(clause,p);
    // }
    // uint o = texelFetch(tapeSampler,i).g;
    // return ram[o];
    float planet = sphereDistance(p,vec3(-50,0,60),10*(1+pulseL));
    float rocket = sceneDistanceCapsule(p,vec3(-40,3,40),vec3(-35,5,40),0.5);
    float sun = sphereDistance(p,vec3(30,0,60),30*(1+pulseR));
    float d = min(sun,planet);
    d = min(d,rocket);
    return d;
}

// finite difference method
vec3 getNormal(in vec3 p) {
    float d = sceneDistance(p);
    vec3 n = d - vec3(
        sceneDistance(p-vec3(SURFACE_DIST,0,0)),
        sceneDistance(p-vec3(0,SURFACE_DIST,0)),
        sceneDistance(p-vec3(0,0,SURFACE_DIST))
    );
    return normalize(n);
}


float march(vec3 rayOrigin, vec3 rayDirection) {
    float originDistance = 0;
    for (int i = 0; i<MAX_STEPS; i++) {
        vec3 p = rayOrigin + originDistance*rayDirection;
        float sceneDistance = sceneDistance(p);
        originDistance += sceneDistance;
        if(sceneDistance < SURFACE_DIST || originDistance > MAX_DIST) break;
    }
    return originDistance;
}

vec3 getLight(in vec3 p) {
    vec3 lightPos = vec3(0,5,-6);
    vec3 l = normalize(lightPos-p);
    vec3 n = getNormal(p);
    // dot returns between -1 and 1, since both l and n are length 1
    float diffuse = clamp(dot(n,l),0,1);
    // shadowing
    float distance = march(p + n*SURFACE_DIST*2,l);
    if (distance < length(lightPos-p)){ // in shadow
        diffuse *= 0.1;
    }
    return vec3(diffuse);
}

void main()
{
    vec2 normFragPos = (gl_FragCoord.xy-0.5*iResolution)/iResolution.y;
    vec3 rayOrigin = vec3(0,1,0);
    vec3 rayDirection = normalize(vec3(normFragPos.x,normFragPos.y,1));
    float dist = march(rayOrigin,rayDirection);

    vec3 position = rayOrigin + rayDirection*dist;
    vec3 diffuse = getLight(position);
    color = vec4(diffuse,1);
}

// Ableitung von gradient -> normale
// pick surface distance as delta
// display normals
// bounding boxs
