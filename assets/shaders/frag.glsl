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

#define MAX_STEPS 10000
#define SURFACE_DIST 0.001
#define MAX_DIST 1000 // avoid stepping into infinity
#define PI 3.1415926538
#define HSIZE 32
#define HSIZEF 32.0
// todo histogram name

out vec4 color;
uniform usamplerBuffer tapeSampler;
uniform uint tapeSize;
uniform samplerBuffer ramSampler;
uniform uint ramSize;
uniform vec2 iResolution;
uniform float pulseL;
uniform float pulseR;
uniform float histogram[HSIZE];

uniform sampler2D woodTexture;
uniform sampler2D duckTexture;

uniform vec3 cameraPos;
uniform mat4 view;

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

// our lord and saviour todo understand
// https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
float smoothSubtraction(float d1, float d2, float k)
{
    float h = max(k-abs(-d1-d2),0.0);
    return max(-d1, d2) + h*h*0.25/k;
    // float h = clamp( 0.5 - 0.5*(d2+d1)/k, 0.0, 1.0 );
    // return mix( d2, -d1, h ) + k*h*(1.0-h);
}

float smoothUnion(float d1, float d2, float k)
{
    float h = max(k-abs(d1-d2),0.0);
    return min(d1, d2) - h*h*0.25/k;
    //float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    //return mix( d2, d1, h ) - k*h*(1.0-h);
}


float sceneDistanceCuboid(in vec3 p, in vec3 center, in vec3 size, float r){
    vec3 q = abs(p-center) - size;
    return length(max(q,0.0))+min(max(q.x,max(q.y,q.z)),0.0)-r;
}

float capsuleDistance(in vec3 p, in vec3 startSphere, in vec3 endSphere, float radius){
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
    // float planet = sphereDistance(p,vec3(-50,0,60),10*(1+pulseL));
    // float rocket = sceneDistanceCapsule(p,vec3(-40*(1-pulseL),3,40),vec3(-35*(1-pulseR),5,40),0.5);
    // float sun = sphereDistance(p,vec3(30,0,60),30*(1+pulseR));
    float boxL = sceneDistanceCuboid(p,vec3(-5,1.9,10),vec3(2,4.2,2),0.2);
    float boxLS = sphereDistance(p,vec3(-5,2,8),1+min(pulseL,1));
    boxL = smoothSubtraction(boxLS, boxL, 0.25);
    float boxR = sceneDistanceCuboid(p,vec3(5,1.9,10),vec3(2,4.2,2),0.2);
    float boxRS = sphereDistance(p,vec3(5,2,8),1+min(pulseR,1));
    boxR = smoothSubtraction(boxRS, boxR, 0.25);
    float d = min(boxL,boxR);
    float connectorb = capsuleDistance(p,vec3(-3,2,11),vec3(3,5,11),-0.1+0.2*min(pulseL,1));
    float connectort = capsuleDistance(p,vec3(-3,5,11),vec3(3,2,11),-0.1+0.2*min(pulseR,1));
    d = smoothUnion(connectorb,d,1.3);
    d = smoothUnion(connectort,d,1.3);
    // todo some artifacts
    // using branching
    // todo can we do that better? can we actually use multiple graph from the complex values
    if(p.x < 5 && p.x > -5 && p.y < 5 && p.y > 0 && p.z > 10 && p.z < 14){
        for(int i=0; i < HSIZE; i++){
            float v = min(histogram[i],4);
            vec3 pos = vec3((i/HSIZEF-0.5)*5.8,v/2.0,11);
            vec3 size = vec3(1/HSIZEF,v,0.1);
            float box = sceneDistanceCuboid(p,pos, size,0);
            d = min(d,box);
        }
    }
    return min(d,p.y);
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

float ambientOcclusion(in vec3 p, vec3 n, float stepDistance, float stepNumber){
    float occlusion = 1.0f;
    while (stepNumber > 0.0){
        float dist = sceneDistance(p+n*stepNumber*stepDistance);
        occlusion -= pow(stepNumber * stepDistance - dist,2) / stepNumber;
        stepNumber--;
    }
    return occlusion;
}

float softshadow( in vec3 ro, in vec3 rd, float mint, float maxt, float k ) {
    float res = 1.0;
    for( float t=mint; t<maxt; )
    {
        float h = sceneDistance(ro + rd*t);
        if( h<0.001 ) return 0.0;
        res = min( res, k*h/t );
        t += h;
    }
    return res;
}

float getLight(in vec3 p, in vec3 n) {
    vec3 lightPos = vec3(0,10,-6);
    vec3 l = normalize(lightPos-p);
    // dot returns between -1 and 1, since both l and n are length 1
    float s = softshadow(p+n*SURFACE_DIST*2,l,SURFACE_DIST,MAX_DIST,64);
    float diffuse = clamp(dot(n,l),0,1) * s;
    // shadowing
    // float distance = march(p + n*SURFACE_DIST*2,l);
    // if (distance < length(lightPos-p)){ // in shadow
    //     diffuse *= 0.1;
    // }
    diffuse*=ambientOcclusion(p,n,0.25,5);
    diffuse*=clamp(0.0,1,0.6+(pulseR+pulseR)*0.5);
    return diffuse;
}

vec3 getColor(in vec3 p, vec3 n){
    vec3 col = vec3(0.1);
    vec3 colorXZ = texture(woodTexture, p.xz*0.5+0.5).rgb;
    vec3 colorYZ = texture(woodTexture, p.zy*0.5+0.5).rgb;
    vec3 colorXY = texture(woodTexture, p.xy*0.5+0.5).rgb;
    vec3 absN = abs(n);
    vec3 mixedSides = colorXZ * absN.y +colorYZ * absN.x + colorXY * absN.z;
    vec4 wood = vec4(mixedSides, smoothstep(0.0,0.05, p.y));
    col = mix(col,wood.rgb,wood.a);

    vec4 duck = texture(duckTexture,-abs(p.xy)*0.4+0.5);
    float duckStrength = clamp(0,1,0.2+(pulseL+pulseR));
    duck = vec4(mix(duck.rgb,vec3(1),duckStrength),duck.a);
    float duckSlider = smoothstep(3.7,3.75,p.y) * smoothstep(6.1,6.0,p.y);;
    float strengthRight = smoothstep(3.5,3.6,p.x)*smoothstep(6.1,6.0,p.x);
    float strengthLeft = smoothstep(-3.8,-3.9,p.x)*smoothstep(-6.1,-6.0,p.x);
    duckSlider *= max(strengthLeft,strengthRight);
    col = mix(col, duck.rgb,duck.a*duckSlider);

    return col;
}

void main()
{
    vec2 normFragPos = (gl_FragCoord.xy-0.5*iResolution)/iResolution.y;
    vec4 rd = view * vec4(normFragPos.x,normFragPos.y+0.0,1,0);
    vec3 rayDirection = normalize(rd.xyz);
    float dist = march(cameraPos,rayDirection);

    vec3 position = cameraPos + rayDirection*dist;
    vec3 n = getNormal(position);
    float diffuse = getLight(position,n);
    color = vec4(getColor(position,n) * diffuse,1);
}

