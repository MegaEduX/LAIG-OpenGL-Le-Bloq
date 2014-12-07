//
//  ANFParser.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <string.h>

#include "ANFParser.h"

#include "Global.h"

#include "Additions.h"

#ifdef _WIN32

    #define kPathDelimiter "\\"

#else

    #define kPathDelimiter "/"

#endif

using namespace std;

void _split(vector<string> &tokens, const string &text, char sep) {
    int start = 0, end = 0;
    
    while ((end = (int) text.find(sep, start)) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    
    tokens.push_back(text.substr(start));
}

std::vector<float> _parseFloatString(std::string fs) {
    std::vector<float> ret;
    
    std::vector<std::string> tokens;
    
    _split(tokens, fs, ' ');
    
	for (int i = 0; i < tokens.size(); i++)
        ret.push_back(stof(tokens[i].c_str()));
    
    return ret;
}

Coordinate3D _parseControlPoint(TiXmlElement *cp) {
    if (!cp->Attribute("xx"))
        throw new ANFAnimationParserException("\"xx\" attribute not found.");
    
    std::vector<float> xxvec = _parseFloatString(cp->Attribute("xx"));
    
    if (xxvec.size() != 1)
        throw new ANFAnimationParserException(&"Invalid xx - expected 1 argument, found " [ xxvec.size()]);
    
    float xx = xxvec[0];
    
    if (!cp->Attribute("yy"))
        throw new ANFAnimationParserException("\"yy\" attribute not found.");
    
    std::vector<float> yyvec = _parseFloatString(cp->Attribute("yy"));
    
    if (yyvec.size() != 1)
        throw new ANFAnimationParserException(&"Invalid yy - expected 1 argument, found " [ yyvec.size()]);
    
    float yy = yyvec[0];
    
    if (!cp->Attribute("zz"))
        throw new ANFAnimationParserException("\"zz\" attribute not found.");
    
    std::vector<float> zzvec = _parseFloatString(cp->Attribute("zz"));
    
    if (zzvec.size() != 1)
        throw new ANFAnimationParserException(&"Invalid zz - expected 1 argument, found " [ zzvec.size()]);
    
    float zz = zzvec[0];
    
    return Coordinate3D(xx, yy, zz);
}

ANFParser::ANFParser(std::string path) {
    _doc = new TiXmlDocument(path.c_str());
    
    if (!(_doc->LoadFile()))
        throw new ANFFileLoadParserException("Unable to load file.");
    
    _setBasePathFromANFPath(path);
}

void ANFParser::_setBasePathFromANFPath(std::string anfPath) {
    _basePath = "";
    
    std::vector<std::string> parts = Additions::explode(kPathDelimiter, anfPath);
    
    parts.erase(parts.end() - 1);
    
	for (int i = 0; i < parts.size(); i++)
        _basePath += parts[i] + kPathDelimiter;
    
    Globals::getInstance().setBasePath(_basePath);
}

ANFResult* ANFParser::parse() {
    ANFResult *result = new ANFResult();
    
    TiXmlElement *element = _doc->FirstChildElement("anf");
    
    if (!element)
        throw new ANFParserException("Unable to get root element (\"anf\").");
    
    //  Globals block is mandatory.
    
    TiXmlElement *globals = element->FirstChildElement("globals");
    
    if (!globals)
        throw new ANFParserException("\"globals\" element not found.");
    
    parseGlobals(globals);
    
    //  Cameras block is mandatory.
    
    TiXmlElement *cameras = element->FirstChildElement("cameras");
    
    if (!cameras)
        throw new ANFParserException("\"cameras\" element not found.");
    
    result->cameras = parseCameras(cameras);
    
    //  Lights block is mandatory.
    
    TiXmlElement *lights = element->FirstChildElement("lights");
    
    if (!lights)
        throw new ANFParserException("\"lights\" element not found.");
    
    result->lights = parseLights(lights);
    
    //  Textures block is mandatory.
    
    TiXmlElement *textures = element->FirstChildElement("textures");
    
    if (!textures)
        throw new ANFParserException("\"textures\" element not found.");
    
    result->textures = parseTextures(textures);
    
    //  Appearances block is NOT mandatory.
    
    TiXmlElement *appearances = element->FirstChildElement("appearances");
    
    if (appearances) {
		std::vector<Appearance *> appr = parseAppearances(appearances);

		/*  for (int i = 0; i < appr.size(); i++)
			result->appearances.push_back(appr[i]); */
        
        result->appearances = appr;
        
        if (!result->appearances.size())
            throw new ANFParserException("\"appearances\" block found, but is empty!");
    }
    
    //  Animations block is NOT mandatory.
    
    TiXmlElement *animations = element->FirstChildElement("animations");
    
    if (animations) {
        std::vector<Animation *> anim = parseAnimations(animations);
        
        result->animations = anim;
        
        if (!result->animations.size())
            throw new ANFParserException("\"animations\" block found, but is empty!");
    }
    
    //  Graphs block
    
    for (TiXmlElement *graph = element->FirstChildElement("graph"); graph != NULL; graph = graph->NextSiblingElement("graph"))
        result->graphs.push_back(parseGraph(graph));
    
    return result;
}

std::vector<Light *> ANFParser::parseLights(TiXmlElement *lights) {
    std::vector<Light *> lightvec;
    
    for (TiXmlElement *li = lights->FirstChildElement("light"); li != NULL; li = li->NextSiblingElement("light")) {
        Light *l = nullptr;
        
        std::string id = "";
        
        if (li->Attribute("id") != NULL)
            id = li->Attribute("id");
        
        if (li->Attribute("enabled") == NULL)
            throw new ANFLightParserException("\"enabled\" attribute not found.");
        
        bool enabled = false;
        
        if (!strcmp(li->Attribute("enabled"), "false"))
            enabled = false;
        else if (!strcmp(li->Attribute("enabled"), "true"))
            enabled = true;
        else
            throw new ANFLightParserException("\"enabled\" expects a boolean value, \"" + std::string(li->Attribute("enabled")) + "\" found.");
        
        if (li->Attribute("marker") == NULL)
            throw new ANFLightParserException("\"marker\" attribute not found.");
        
        bool marker = false;
        
        if (!strcmp(li->Attribute("marker"), "false"))
            marker = false;
        else if (!strcmp(li->Attribute("marker"), "true"))
            marker = true;
        else
            throw new ANFLightParserException("\"marker\" expects a boolean value, \"" + std::string(li->Attribute("marker")) + "\" found.");
        
        if (li->Attribute("pos") == NULL)
            throw new ANFLightParserException("\"pos\" attribute not found.");
        
        std::vector<float> posvec = _parseFloatString(li->Attribute("pos"));
        
        if (posvec.size() != 3)
            throw new ANFLightParserException(&"Invalid position - expected 3 arguments, found " [ posvec.size()]);
        
        Coordinate3D pos = Coordinate3D(posvec[0], posvec[1], posvec[2]);
        
        if (!strcmp(li->Attribute("type"), "omni"))
            
            l = new OmnidirectionalLight(id, enabled, marker, pos);
        
        else if (!strcmp(li->Attribute("type"), "spot")) {
            
            if (li->Attribute("target") == NULL)
                throw new ANFLightParserException("\"target\" attribute not found.");
            
            std::vector<float> targetvec = _parseFloatString(li->Attribute("target"));
            
            if (targetvec.size() != 3)
                throw new ANFLightParserException(&"Invalid position - expected 3 arguments, found " [ targetvec.size()]);
            
            Coordinate3D target = Coordinate3D(targetvec[0], targetvec[1], targetvec[2]);
            
            if (li->Attribute("angle") == NULL)
                throw new ANFLightParserException("\"angle\" attribute not found.");
            
            std::vector<float> anglevec = _parseFloatString(li->Attribute("angle"));
            
            if (anglevec.size() != 1)
                throw new ANFLightParserException(&"Invalid angle - expected 1 argument, found " [ anglevec.size()]);
            
            float angle = anglevec[0];
            
            if (li->Attribute("exponent") == NULL)
                throw new ANFLightParserException("\"exponent\" attribute not found.");
            
            std::vector<float> expvec = _parseFloatString(li->Attribute("exponent"));
            
            if (expvec.size() != 1)
                throw new ANFLightParserException(&"Invalid exponent - expected 1 argument, found " [ expvec.size()]);
            
            float exponent = expvec[0];
            
            l = new SpotlightLight(id, enabled, marker, pos, target, angle, exponent);
            
        } else
            throw new ANFLightParserException("Invalid light type \"" + std::string(li->Value()) + "\".");
        
        for (TiXmlElement *component = li->FirstChildElement("component"); component != NULL; component = component->NextSiblingElement("component"))
            l->addComponent(parseComponent(component));
        
        lightvec.push_back(l);
    }
    
    return lightvec;
}

std::vector<Camera *> ANFParser::parseCameras(TiXmlElement *cameras) {
    std::vector<Camera *> camvec;
    
    if (!cameras->Attribute("initial"))
        throw new ANFCameraParserException("\"initial\" camera attribute not found.");
    
    std::string defaultCamera = cameras->Attribute("initial");
    
    bool defaultSet = false;
    
    for (TiXmlElement *cam = cameras->FirstChildElement(); cam != NULL; cam = cam->NextSiblingElement()) {
        Camera *c = nullptr;
        
        std::string id = "";
        
        if (cam->Attribute("id") != NULL)
            id = cam->Attribute("id");
        
        if (!strcmp(cam->Value(), "perspective")) {
            
            if (cam->Attribute("near") == NULL)
                throw new ANFCameraParserException("\"near\" attribute not found.");
            
            std::vector<float> nearvec = _parseFloatString(cam->Attribute("near"));
            
            if (nearvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"near\" - expected 1 argument, found " [ nearvec.size()]);
            
            float near = nearvec[0];
            
            if (cam->Attribute("far") == NULL)
                throw new ANFCameraParserException("\"far\" attribute not found.");
            
            std::vector<float> farvec = _parseFloatString(cam->Attribute("far"));
            
            if (farvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"far\" - expected 1 argument, found " [ farvec.size()]);
            
            float far = farvec[0];
            
            if (cam->Attribute("angle") == NULL)
                throw new ANFCameraParserException("\"angle\" attribute not found.");
            
            std::vector<float> anglevec = _parseFloatString(cam->Attribute("angle"));
            
            if (anglevec.size() != 1)
                throw new ANFTextureParserException(&"Invalid angle - expected 1 argument, found " [ anglevec.size()]);
            
            float angle = anglevec[0];
            
            if (cam->Attribute("pos") == NULL)
                throw new ANFCameraParserException("\"pos\" attribute not found.");
            
            std::vector<float> posvec = _parseFloatString(cam->Attribute("pos"));
            
            if (posvec.size() != 3)
                throw new ANFTextureParserException(&"Invalid position - expected 3 arguments, found " [ posvec.size()]);
            
            Coordinate3D pos = Coordinate3D(posvec[0], posvec[1], posvec[2]);
            
            if (cam->Attribute("target") == NULL)
                throw new ANFCameraParserException("\"target\" attribute not found.");
            
            std::vector<float> targetvec = _parseFloatString(cam->Attribute("target"));
            
            if (targetvec.size() != 3)
                throw new ANFTextureParserException(&"Invalid target - expected 3 arguments, found " [ targetvec.size()]);
            
            Coordinate3D target = Coordinate3D(targetvec[0], targetvec[1], targetvec[2]);
            
            c = new PerspectiveCamera(id, near, far, angle, pos, target);
            
        } else if (!strcmp(cam->Value(), "ortho")) {
            
            const char *dir = cam->Attribute("direction");
            
            if (!dir)
                throw new ANFCameraParserException("\"direction\" attribute not found.");
            
            if (dir[0] != 'x' && dir[0] != 'y' && dir[0] != 'z')
                throw new ANFNodeParserException("Invalid axis (" + std::string(dir) + ").");
            
            std::vector<float> nearvec = _parseFloatString(cam->Attribute("near"));
            
            if (nearvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"near\" - expected 1 argument, found " [ nearvec.size()]);
            
            float near = nearvec[0];
            
            if (cam->Attribute("far") == NULL)
                throw new ANFCameraParserException("\"far\" attribute not found.");
            
            std::vector<float> farvec = _parseFloatString(cam->Attribute("far"));
            
            if (farvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"far\" - expected 1 argument, found " [ farvec.size()]);
            
            float far = farvec[0];
            
            if (cam->Attribute("left") == NULL)
                throw new ANFCameraParserException("\"left\" attribute not found.");
            
            std::vector<float> leftvec = _parseFloatString(cam->Attribute("left"));
            
            if (leftvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"left\" - expected 1 argument, found " [ leftvec.size()]);
            
            float left = leftvec[0];
            
            if (cam->Attribute("right") == NULL)
                throw new ANFCameraParserException("\"right\" attribute not found.");
            
            std::vector<float> rightvec = _parseFloatString(cam->Attribute("right"));
            
            if (rightvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"right\" - expected 1 argument, found " [ rightvec.size()]);
            
            float right = rightvec[0];
            
            if (cam->Attribute("top") == NULL)
                throw new ANFCameraParserException("\"top\" attribute not found.");
            
            std::vector<float> topvec = _parseFloatString(cam->Attribute("top"));
            
            if (topvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"top\" - expected 1 argument, found " [ topvec.size()]);
            
            float top = topvec[0];
            
            if (cam->Attribute("bottom") == NULL)
                throw new ANFCameraParserException("\"bottom\" attribute not found.");
            
            std::vector<float> bottomvec = _parseFloatString(cam->Attribute("bottom"));
            
            if (bottomvec.size() != 1)
                throw new ANFTextureParserException(&"Invalid \"bottomvec\" - expected 1 argument, found " [ bottomvec.size()]);
            
            float bottom = bottomvec[0];
            
            c = new OrthographicCamera(id, dir[0], near, far, left, right, top, bottom);
            
        } else
            throw new ANFCameraParserException("Invalid camera type \"" + std::string(cam->Value()) + "\".");
        
        if (id == defaultCamera) {
            c->setEnabled(true);
            
            defaultSet = true;
        }
        
        camvec.push_back(c);
    }
    
    if (!defaultSet)
        throw new ANFCameraParserException("Default camera not found!");
    
    return camvec;
}

std::vector<Texture *> ANFParser::parseTextures(TiXmlElement *textures) {
    std::vector<Texture *> texvec;
    
    for (TiXmlElement *tex = textures->FirstChildElement("texture"); tex != NULL; tex = tex->NextSiblingElement("texture")) {
        std::string id = "";
        
        if (tex->Attribute("id") != NULL)
            id = tex->Attribute("id");
        
        if (!(tex->Attribute("file")))
            throw new ANFTextureParserException("\"file\" attribute not found.");
        
        std::string filePath = _basePath + tex->Attribute("file");
        
        if (!(tex->Attribute("texlength_s")))
            throw new ANFTextureParserException("\"texlength_s\" attribute not found.");
        
        std::vector<float> tlsvec = _parseFloatString(tex->Attribute("texlength_s"));
        
        if (tlsvec.size() != 1)
            throw new ANFTextureParserException(&"Invalid texture length (s) - expected 1 argument, found " [ tlsvec.size()]);
        
        float texlength_s = tlsvec[0];
        
        if (!(tex->Attribute("texlength_t")))
            throw new ANFTextureParserException("\"texlength_t\" attribute not found.");
        
        std::vector<float> tltvec = _parseFloatString(tex->Attribute("texlength_t"));
        
        if (tltvec.size() != 1)
            throw new ANFTextureParserException(&"Invalid texture length (t) - expected 1 argument, found " [ tltvec.size()]);
        
        float texlength_t = tltvec[0];

		kTexLength len;

		len.s = texlength_s;
		len.t = texlength_t;
        
        texvec.push_back(new Texture(id, filePath, len));
    }
    
    return texvec;
}

std::vector<Animation *> ANFParser::parseAnimations(TiXmlElement *animations) {
    std::vector<Animation *> anivec;
    
    for (TiXmlElement *ani = animations->FirstChildElement("animation"); ani != NULL; ani = ani->NextSiblingElement("animation")) {
        std::string id = "";
        
        if (ani->Attribute("id") != NULL)
            id = ani->Attribute("id");
        
        bool hidden = false;
        
        if (ani->Attribute("hidden")) {
            std::string hid = ani->Attribute("hidden");
            
            if (hid == "true")
                hidden = true;
            else if (hid == "false")
                hidden = false;
            else
                throw new ANFAnimationParserException("\"hidden\" must be either true or false!");
        }
        
        int span = 0;
        
        if (strcmp(ani->Attribute("type"), "composite")) {
            if (!(ani->Attribute("span")))
                throw new ANFAnimationParserException("\"span\" attribute not found.");
            
            std::vector<float> spanvec = _parseFloatString(ani->Attribute("span"));
            
            if (spanvec.size() != 1)
                throw new ANFAnimationParserException(std::string("Integer expected for \"span\", found") + ani->Attribute("span"));
            
            span = spanvec[0];
        }
        
        if (!ani->Attribute("type"))
            throw new ANFAnimationParserException("\"type\" attribute not found.");
        
        if (!strcmp(ani->Attribute("type"), "linear")) {
            
            LinearAnimation *la = new LinearAnimation(id, span);
            
            for (TiXmlElement *cp = ani->FirstChildElement("controlpoint"); cp != NULL; cp = cp->NextSiblingElement("controlpoint"))
                la->addControlPoint(_parseControlPoint(cp));
            
            la->setHidden(hidden);
            
            anivec.push_back(la);
            
        } else if (!strcmp(ani->Attribute("type"), "circular")) {
            
            if (!ani->Attribute("center"))
                throw new ANFAnimationParserException("\"center\" attribute not found.");
            
            std::vector<float> cenvec = _parseFloatString(ani->Attribute("center"));
            
            if (cenvec.size() != 3)
                throw new ANFAnimationParserException(&"Invalid animation center - expected 3 arguments, found " [ cenvec.size()]);
            
            Coordinate3D center = Coordinate3D(cenvec[0], cenvec[1], cenvec[2]);
            
            if (!ani->Attribute("radius"))
                throw new ANFAnimationParserException("\"radius\" attribute not found.");
            
            std::vector<float> radvec = _parseFloatString(ani->Attribute("radius"));
            
            if (radvec.size() != 1)
                throw new ANFAnimationParserException(&"Invalid radius - expected 1 argument, found " [ radvec.size()]);
            
            float radius = radvec[0];
            
            if (!ani->Attribute("startang"))
                throw new ANFAnimationParserException("\"startang\" attribute not found.");
            
            std::vector<float> savec = _parseFloatString(ani->Attribute("startang"));
            
            if (savec.size() != 1)
                throw new ANFAnimationParserException(&"Invalid start angle - expected 1 argument, found " [ savec.size()]);
            
            float startang = savec[0];
            
            if (!ani->Attribute("rotang"))
                throw new ANFAnimationParserException("\"rotang\" attribute not found.");
            
            std::vector<float> ravec = _parseFloatString(ani->Attribute("rotang"));
            
            if (ravec.size() != 1)
                throw new ANFAnimationParserException(&"Invalid radius - expected 1 argument, found " [ ravec.size()]);
            
            float rotang = ravec[0];
            
            CircularAnimation *anim = new CircularAnimation(id, span, center, radius, startang, rotang);
            
            anim->setHidden(hidden);
            
            anivec.push_back(anim);
            
        } else if (!strcmp(ani->Attribute("type"), "composite")) {
            
            std::vector<std::string> animationRefs;
            
            for (TiXmlElement *ref = ani->FirstChildElement("animationref"); ref != NULL; ref = ref->NextSiblingElement("animationref")) {
                const char *animId = ref->Attribute("id");
                
                if (animId == NULL)
                    throw new ANFNodeParserException("\"animation\" ref block found, but was empty...");
                
                animationRefs.push_back(animId);
            }
            
            CompositeAnimation *anim = new CompositeAnimation(id, animationRefs);
            
            anim->setHidden(hidden);
            
            anivec.push_back(anim);
        
        } else
            throw new ANFAnimationParserException(std::string("Unknown type \"") + ani->Attribute("type") + "\".");
    }
    
    return anivec;
}

Graph *ANFParser::parseGraph(TiXmlElement *graph) {
    Graph *gp = new Graph();
    
    if (graph->Attribute("rootid"))
        gp->setRootNodeRef(graph->Attribute("rootid"));
    
    for (TiXmlElement *node = graph->FirstChildElement("node"); node != NULL; node = node->NextSiblingElement("node"))
        gp->addNode(parseNode(node));
    
    if (!(gp->getNodes().size()))
        throw new ANFParserException("A graph requires at least a node!");
    
    return gp;
}

Node *ANFParser::parseNode(TiXmlElement *node) {
    Node *nd = new Node();
    
    if (node->Attribute("id"))
        nd->setId(node->Attribute("id"));
    
    if (node->Attribute("displaylist")) {
        if (!strcmp(node->Attribute("displaylist"), "true"))
            nd->setUseDisplayList(true);
        else if (!strcmp(node->Attribute("displaylist"), "false"))
            nd->setUseDisplayList(false);
        else
            throw new ANFNodeParserException(std::string("Boolean expected, found ") + node->Attribute("displaylist"));
    }
    
    for (TiXmlElement *nodeElem = node->FirstChildElement(); nodeElem != NULL; nodeElem = nodeElem->NextSiblingElement()) {
        if (!strcmp(nodeElem->Value(), "transforms")) {

			std::vector<Transform *> transf = parseTransforms(nodeElem);
			
			for (int i = 0; i < transf.size(); i++)
				nd->addTransform(transf[i]);

		} else if (!strcmp(nodeElem->Value(), "primitives")) {

			std::vector<Primitive *> prims = parsePrimitives(nodeElem);
			
			for (int i = 0; i < prims.size(); i++)
				nd->addPrimitive(prims[i]);

		} else if (!strcmp(nodeElem->Value(), "appearanceref")) {
            
            const char *id = nodeElem->Attribute("id");
            
            if (id == NULL)
                throw new ANFNodeParserException("\"appearance\" ref block found, but was empty...");
            
            nd->setAppearanceRef(id);
            
        } else if (!strcmp(nodeElem->Value(), "animationref")) {
            
            const char *id = nodeElem->Attribute("id");
            
            if (id == NULL)
                throw new ANFNodeParserException("\"animation\" ref block found, but was empty...");
            
            nd->setAnimationRef(id);
            
        } else if (!strcmp(nodeElem->Value(), "descendants"))
            
            for (TiXmlElement *desc = nodeElem->FirstChildElement("noderef"); desc != NULL; desc = desc->NextSiblingElement("noderef")) {
                if (desc->Attribute("id"))
                    nd->addNodeRef(desc->Attribute("id"));
                else
                    throw new ANFNodeParserException("An \"id\" is required on a noderef!");
            }
        
    }
    
    return nd;
}

std::vector<Appearance *> ANFParser::parseAppearances(TiXmlElement *appearances) {
    std::vector<Appearance *> appvec;
    
    for (TiXmlElement *appearance = appearances->FirstChildElement("appearance"); appearance != NULL; appearance = appearance->NextSiblingElement("appearance")) {
        std::string appId = (appearance->Attribute("id") != NULL ? appearance->Attribute("id") : "");
        
        float shininess = _parseFloatString(appearance->Attribute("shininess"))[0];
        
        Appearance *app = new Appearance(appId, shininess);
        
        if (appearance->Attribute("textureref"))
            app->setTextureRef(appearance->Attribute("textureref"));
        
        for (TiXmlElement *component = appearance->FirstChildElement("component"); component != NULL; component = component->NextSiblingElement("component"))
            app->addComponent(parseComponent(component));
        
        appvec.push_back(app);
    }
    
    return appvec;
}

Component* ANFParser::parseComponent(TiXmlElement *component) {
    const char *type = component->Attribute("type");
    
    if (!type)
        throw new ANFAppearanceParserException("\"type\" attribute not found.");
    
    kComponentType ct;
    
    if (!strcmp(type, "ambient"))
        ct = kComponentTypeAmbient;
    else if (!strcmp(type, "diffuse"))
        ct = kComponentTypeDiffuse;
    else if (!strcmp(type, "specular"))
        ct = kComponentTypeSpecular;
    else
        throw new ANFAppearanceParserException("Invalid component type!");
    
    const char *value = component->Attribute("value");
    
    if (!value)
        throw new ANFAppearanceParserException("\"value\" attribute not found.");
    
    std::vector<float> valvec = _parseFloatString(value);
    
    if (valvec.size() != 4)
        throw new ANFNodeParserException(std::string(&"Color expected, found " [ valvec.size()]) + std::string(" elements."));
    
	kColorRGB color;

	color.r = valvec[0];
	color.g = valvec[1];
	color.b = valvec[2];
	color.a = valvec[3];
    
    return new Component(ct, color);
}

std::vector<Transform *> ANFParser::parseTransforms(TiXmlElement *transforms) {
    std::vector<Transform *> trfvec;
    
    for (TiXmlElement *transform = transforms->FirstChildElement("transform"); transform != NULL; transform = transform->NextSiblingElement("transform")) {
        Transform *trf = nullptr;
        
        if (!strcmp(transform->Attribute("type"), "translate")) {
            
            const char *to = transform->Attribute("to");
            
            if (!to)
                throw new ANFNodeParserException("\"to\" attribute not found.");
            
            std::vector<float> fs = _parseFloatString(to);
            
            if (fs.size() != 3)
                throw new ANFNodeParserException(&"Invalid coordinates - expected 3 arguments, found " [ fs.size()]);
            
            trf = new Translate(Coordinate3D(fs[0], fs[1], fs[2]));
            
        } else if (!strcmp(transform->Attribute("type"), "rotate")) {
            
            const char *axis = transform->Attribute("axis");
            
            if (!axis)
                throw new ANFNodeParserException("\"axis\" attribute not found.");
            
            if (axis[0] != 'x' && axis[0] != 'y' && axis[0] != 'z')
                throw new ANFNodeParserException("Invalid axis (" + std::string(axis) + ").");
            
            const char *angle = transform->Attribute("angle");
            
            if (!angle)
                throw new ANFNodeParserException("\"angle\" attribute not found.");
            
            trf = new Rotate(axis[0], stof(angle));
            
        } else if (!strcmp(transform->Attribute("type"), "scale")) {
            
            const char *factor = transform->Attribute("factor");
            
            if (!factor)
                throw new ANFNodeParserException("\"factor\" attribute not found.");
            
            std::vector<float> fs = _parseFloatString(factor);
            
            if (fs.size() != 3)
                throw new ANFNodeParserException(&"Invalid coordinates - expected 3 arguments, found " [ fs.size()]);
            
            trf = new Scale(Coordinate3D(fs[0], fs[1], fs[2]));
            
        } else
            throw new ANFNodeParserException("Unsupported transformation: \"" + std::string(transform->Attribute("type")) + "\".");
        
        trfvec.push_back(trf);
    }
    
    return trfvec;
}

std::vector<Primitive *> ANFParser::parsePrimitives(TiXmlElement *primitives) {
    std::vector<Primitive *> primvec;
    
    for (TiXmlElement *primitive = primitives->FirstChildElement(); primitive != NULL; primitive = primitive->NextSiblingElement()) {
        Primitive *prim = nullptr;
        
        if (!strcmp(primitive->Value(), "rectangle")) {
            
            const char *xy1 = primitive->Attribute("xy1");
            
            if (!xy1)
                throw new ANFNodeParserException("\"xy1\" attribute not found.");
            
            std::vector<float> xy1vec = _parseFloatString(xy1);
            
            if (xy1vec.size() != 2)
                throw new ANFNodeParserException(std::string(&"2D coordinate expected, found " [ xy1vec.size()]) + std::string(" elements."));
            
            Coordinate2D xy1cd = Coordinate2D(xy1vec[0], xy1vec[1]);
            
            const char *xy2 = primitive->Attribute("xy2");
            
            if (!xy2)
                throw new ANFNodeParserException("\"xy2\" attribute not found.");
            
            std::vector<float> xy2vec = _parseFloatString(xy2);
            
            if (xy2vec.size() != 2)
                throw new ANFNodeParserException(std::string(&"2D coordinate expected, found " [ xy1vec.size()]) + std::string(" elements."));
            
            Coordinate2D xy2cd = Coordinate2D(xy2vec[0], xy2vec[1]);
            
            prim = new Rectangle(xy1cd, xy2cd);
            
        } else if (!strcmp(primitive->Value(), "triangle")) {
            
            std::vector<std::string> attributes;

			attributes.push_back("xyz1");
			attributes.push_back("xyz2");
			attributes.push_back("xyz3");
            
            std::vector<Coordinate3D> coordinates;
            
			for (int i = 0; i < attributes.size(); i++) {
				std::string attr = attributes[i];
				
                const char *xyz = primitive->Attribute(attr.c_str());
                
                if (!xyz)
                    throw new ANFNodeParserException("\"" + attr + "\" attribute not found.");
                
                std::vector<float> xyzvec = _parseFloatString(xyz);
                
                if (xyzvec.size() != 3)
                    throw new ANFNodeParserException(std::string(&"3D coordinate expected, found " [ xyzvec.size()]) + std::string(" elements."));
                
                coordinates.push_back(Coordinate3D(xyzvec[0], xyzvec[1], xyzvec[2]));
            }
            
            prim = new Triangle(coordinates[0], coordinates[1], coordinates[2]);
            
        } else if (!strcmp(primitive->Value(), "cylinder")) {
            
            float basef = 0.0f;
            
            {
                const char *base = primitive->Attribute("base");
                
                if (!base)
                    throw new ANFNodeParserException("\"base\" attribute not found.");
                
                std::vector<float> basevec = _parseFloatString(base);
                
                if (basevec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ basevec.size()]) + std::string(" elements."));
                
                basef = basevec[0];
            }
            
            float topf = 0.0f;
            
            {
                const char *top = primitive->Attribute("top");
                
                if (!top)
                    throw new ANFNodeParserException("\"top\" attribute not found.");
                
                std::vector<float> topvec = _parseFloatString(top);
                
                if (topvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ topvec.size()]) + std::string(" elements."));
                
                topf = topvec[0];
            }
            
            float heightf = 0.0f;
            
            {
                const char *height = primitive->Attribute("height");
                
                if (!height)
                    throw new ANFNodeParserException("\"height\" attribute not found.");
                
                std::vector<float> heightvec = _parseFloatString(height);
                
                if (heightvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ heightvec.size()]) + std::string(" elements."));
                
                heightf = heightvec[0];
            }
            
            int slicesi = 0;
            
            {
                const char *slices = primitive->Attribute("slices");
                
                if (!slices)
                    throw new ANFNodeParserException("\"slices\" attribute not found.");
                
                std::vector<float> slicesvec = _parseFloatString(slices);
                
                if (slicesvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ slicesvec.size()]) + std::string(" elements."));
                
                slicesi = slicesvec[0];
            }
            
            int stacksi = 0;
            
            {
                const char *stacks = primitive->Attribute("stacks");
                
                if (!stacks)
                    throw new ANFNodeParserException("\"stacks\" attribute not found.");
                
                std::vector<float> stacksvec = _parseFloatString(stacks);
                
                if (stacksvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ stacksvec.size()]) + std::string(" elements."));
                
                stacksi = stacksvec[0];
            }
            
            prim = new Cylinder(basef, topf, heightf, slicesi, stacksi);
                
        } else if (!strcmp(primitive->Value(), "sphere")) {
            
            float radiusf = 0.0f;
            
            {
                const char *radius = primitive->Attribute("radius");
                
                if (!radius)
                    throw new ANFNodeParserException("\"radius\" attribute not found.");
                
                std::vector<float> radiusvec = _parseFloatString(radius);
                
                if (radiusvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ radiusvec.size()]) + std::string(" elements."));
                
                radiusf = radiusvec[0];
            }
            
            int slicesi = 0;
            
            {
                const char *slices = primitive->Attribute("slices");
                
                if (!slices)
                    throw new ANFNodeParserException("\"slices\" attribute not found.");
                
                std::vector<float> slicesvec = _parseFloatString(slices);
                
                if (slicesvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ slicesvec.size()]) + std::string(" elements."));
                
                slicesi = slicesvec[0];
            }
            
            int stacksi = 0;
            
            {
                const char *stacks = primitive->Attribute("stacks");
                
                if (!stacks)
                    throw new ANFNodeParserException("\"stacks\" attribute not found.");
                
                std::vector<float> stacksvec = _parseFloatString(stacks);
                
                if (stacksvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ stacksvec.size()]) + std::string(" elements."));
                
                stacksi = stacksvec[0];
            }
            
            prim = new Sphere(radiusf, slicesi, stacksi);
            
        } else if (!strcmp(primitive->Value(), "torus")) {
            
            float innerf = 0.0f;
            
            {
                const char *inner = primitive->Attribute("inner");
                
                if (!inner)
                    throw new ANFNodeParserException("\"inner\" attribute not found.");
                
                std::vector<float> innervec = _parseFloatString(inner);
                
                if (innervec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ innervec.size()]) + std::string(" elements."));
                
                innerf = innervec[0];
            }
            
            float outerf = 0.0f;
            
            {
                const char *outer = primitive->Attribute("outer");
                
                if (!outer)
                    throw new ANFNodeParserException("\"outer\" attribute not found.");
                
                std::vector<float> outervec = _parseFloatString(outer);
                
                if (outervec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"float expected, found " [ outervec.size()]) + std::string(" elements."));
                
                outerf = outervec[0];
            }
            
            float slicesi = 0;
            
            {
                const char *slices = primitive->Attribute("slices");
                
                if (!slices)
                    throw new ANFNodeParserException("\"slices\" attribute not found.");
                
                std::vector<float> slicesvec = _parseFloatString(slices);
                
                if (slicesvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ slicesvec.size()]) + std::string(" elements."));
                
                slicesi = slicesvec[0];
            }
            
            float loopsi = 0;
            
            {
                const char *loops = primitive->Attribute("loops");
                
                if (!loops)
                    throw new ANFNodeParserException("\"loops\" attribute not found.");
                
                std::vector<float> loopsvec = _parseFloatString(loops);
                
                if (loopsvec.size() != 1)
                    throw new ANFNodeParserException(std::string(&"integer expected, found " [ loopsvec.size()]) + std::string(" elements."));
                
                loopsi = loopsvec[0];
            }
            
            prim = new Torus(innerf, outerf, slicesi, loopsi);
            
        } else if (!strcmp(primitive->Value(), "plane")) {
            
            const char *parts = primitive->Attribute("parts");
            
            if (!parts)
                throw new ANFNodeParserException("\"parts\" attribute not found.");
            
            std::vector<float> partsvec = _parseFloatString(parts);
            
            if (partsvec.size() != 1)
                throw new ANFNodeParserException(std::string(&"Integer expected, found " [ partsvec.size()]) + std::string(" elements."));
            
            prim = new Plane(partsvec[0]);
            
        } else if (!strcmp(primitive->Value(), "patch")) {
            
            const char *order = primitive->Attribute("order");
            
            std::vector<float> orderVec = _parseFloatString(order);
            
            if (orderVec.size() != 1)
                throw new ANFNodeParserException(std::string(&"Integer expected, found " [ orderVec.size()]) + std::string(" elements."));
            
            if (orderVec[0] < 1 || orderVec[0] > 3)
                throw new ANFNodeParserException("\"order\" must be an integer between 1 and 3.");
            
            const char *partsU = primitive->Attribute("partsU");
            
            std::vector<float> partsUVec = _parseFloatString(partsU);
            
            if (partsUVec.size() != 1)
                throw new ANFNodeParserException(std::string(&"Integer expected, found " [ partsUVec.size()]) + std::string(" elements."));
            
            const char *partsV = primitive->Attribute("partsV");
            
            std::vector<float> partsVVec = _parseFloatString(partsV);
            
            if (partsVVec.size() != 1)
                throw new ANFNodeParserException(std::string(&"Integer expected, found " [ partsVVec.size()]) + std::string(" elements."));
            
            kPatchCompute pc;
            
            std::string compute = primitive->Attribute("compute");
            
            if (compute == "point")
                pc = kPatchComputePoint;
            else if (compute == "line")
                pc = kPatchComputeLine;
            else if (compute == "fill")
                pc = kPatchComputeFill;
            else
                throw new ANFNodeParserException("Undefined compute \"" + compute + "\".");
            
            prim = new Patch(orderVec[0], Coordinate2D(partsUVec[0], partsVVec[0]), pc);
            
            int expectedControlPoints = pow(orderVec[0] + 1, 2);
            
            int cps = 0;
            
            for (TiXmlElement *cp = primitive->FirstChildElement("controlpoint"); cp != NULL; cps++, cp = cp->NextSiblingElement("controlpoint"))
                ((Patch *) prim)->addControlPoint(_parseControlPoint(cp));
            
            if (expectedControlPoints != cps)
            throw new ANFNodeParserException(std::string("Expected ") + std::to_string(expectedControlPoints) + std::string(" control points, found ") + std::to_string(cps) + std::string("!"));
            
        } else if (!strcmp(primitive->Value(), "table")) {
            
            prim = new Table();
            
        } else if (!strcmp(primitive->Value(), "cube")) {
            
            prim = new UnitCube();
            
        } else if (!strcmp(primitive->Value(), "flag")) {
            
            const char *tex = primitive->Attribute("texture");
            
            if (!tex)
                throw new ANFNodeParserException("\"texture\" attribute not found!");
            
            kTexLength len;
            
            len.s = 1;
            len.t = 1;
            
            Texture *t = new Texture(tex, _basePath + tex, len);
            
            prim = new Flag(t);
            
        } else if (!strcmp(primitive->Value(), "vehicle"))
            
            prim = new Vehicle();
            
        else
            throw new ANFNodeParserException("Found an unexpected entry \"" + std::string(primitive->Value()) + "\".");
        
        primvec.push_back(prim);
    }
    
    return primvec;
}

void ANFParser::parseGlobals(TiXmlElement *globals) {
    for (TiXmlElement *global = globals->FirstChildElement(); global != NULL; global = global->NextSiblingElement()) {
        if (!strcmp(global->Value(), "drawing")) {
            
            //  Mode
            
            const char *mode = global->Attribute("mode");
            
            if (!mode)
                throw new ANFGlobalsParserException("\"mode\" attribute not found.");
            
            kDrawingMode dm;
            
            if (!strcmp(mode, "fill"))
                dm = kDrawingModeFill;
            else if (!strcmp(mode, "line"))
                dm = kDrawingModeLine;
            else if (!strcmp(mode, "point"))
                dm = kDrawingModePoint;
            else
                throw new ANFGlobalsParserException("Invalid drawing mode.");
            
            //  Shading
            
            const char *shading = global->Attribute("shading");
            
            if (!shading)
                throw new ANFGlobalsParserException("\"shading\" attribute not found.");
            
            kDrawingShading ds;
            
            if (!strcmp(shading, "flat"))
                ds = kDrawingShadingFlat;
            else if (!strcmp(shading, "gouraud"))
                ds = kDrawingShadingGouraud;
            else
                throw new ANFGlobalsParserException("Invalid drawing shading.");
            
            //  Background
            
            const char *background = global->Attribute("background");
            
            if (!background)
                throw new ANFGlobalsParserException("\"background\" attribute not found.");
            
            std::vector<float> vecbg = _parseFloatString(background);
            
            if (vecbg.size() != 4)
                throw new ANFGlobalsParserException(&"Invalid background - expected 4 arguments, found " [ vecbg.size()]);
            
			kColorRGB dbg;

			dbg.r = vecbg[0];
			dbg.g = vecbg[1];
			dbg.b = vecbg[2];
			dbg.a = vecbg[3];
            
            Globals::getInstance().setDrawingSettings(new DrawingSettings(dm, ds, dbg));
            
        } else if (!strcmp(global->Value(), "culling")) {
            
            //  Face
            
            const char *face = global->Attribute("face");
            
            if (!face)
                throw new ANFGlobalsParserException("\"face\" attribute not found.");
            
            kCullingFace cf;
            
            if (!strcmp(face, "none"))
                cf = kCullingFaceNone;
            else if (!strcmp(face, "back"))
                cf = kCullingFaceBack;
            else if (!strcmp(face, "front"))
                cf = kCullingFaceFront;
            else if (!strcmp(face, "both"))
                cf = kCullingFaceBoth;
            else
                throw new ANFGlobalsParserException("Invalid culling face.");
            
            //  Order
            
            const char *order = global->Attribute("order");
            
            if (!order)
                throw new ANFGlobalsParserException("\"order\" attribute not found.");
            
            kCullingOrder co;
            
            if (!strcmp(order, "cw"))
                co = kCullingOrderClockWise;
            else if (!strcmp(order, "ccw"))
                co = kCullingOrderCounterClockWise;
            else
                throw new ANFGlobalsParserException("Invalid culling order.");
            
            Globals::getInstance().setCullingSettings(new CullingSettings(cf, co));
            
        } else if (!strcmp(global->Value(), "lighting")) {
            
            //  Double Sided
            
            const char *ds = global->Attribute("doublesided");
            
            if (!ds)
                throw new ANFGlobalsParserException("\"doublesided\" attribute not found.");
            
            bool doubleSided = false;
            
            if (!strcmp(ds, "false"))
                doubleSided = false;
            else if (!strcmp(ds, "true"))
                doubleSided = true;
            else
                throw new ANFGlobalsParserException("\"doublesided\" expects a boolean value, \"" + std::string(ds) + "\" found.");
            
            //  Local
            
            const char *loc = global->Attribute("local");
            
            if (!loc)
                throw new ANFGlobalsParserException("\"local\" attribute not found.");
            
            bool local = false;
            
            if (!strcmp(loc, "false"))
                local = false;
            else if (!strcmp(loc, "true"))
                local = true;
            else
                throw new ANFGlobalsParserException("\"local\" expects a boolean value, \"" + std::string(loc) + "\" found.");
            
            //  Enabled
            
            const char *en = global->Attribute("enabled");
            
            if (!en)
                throw new ANFGlobalsParserException("\"enabled\" attribute not found.");
            
            bool enabled = false;
            
            if (!strcmp(en, "false"))
                enabled = false;
            else if (!strcmp(en, "true"))
                enabled = true;
            else
                throw new ANFGlobalsParserException("\"enabled\" expects a boolean value, \"" + std::string(en) + "\" found.");
            
            //  Ambient
            
            const char *amb = global->Attribute("ambient");
            
            if (!amb)
                throw new ANFGlobalsParserException("\"ambient\" attribute not found.");
            
            std::vector<float> ambbg = _parseFloatString(amb);
            
            if (ambbg.size() != 4)
                throw new ANFGlobalsParserException(&"Invalid background - expected 4 arguments, found " [ ambbg.size()]);

			kColorRGB abg;

			abg.r = ambbg[0];
			abg.g = ambbg[1];
			abg.b = ambbg[2];
			abg.a = ambbg[3];
            
            Globals::getInstance().setLightingSettings(new LightingSettings(doubleSided, local, enabled, abg));
           
        } else if (!strcmp(global->Value(), "shading")) {
            
            const char *fp = global->Attribute("frag_path");
            
            if (!fp)
                throw new ANFGlobalsParserException("\"frag_path\" attribute not found.");
            
            const char *vp = global->Attribute("vert_path");
            
            if (!vp)
                throw new ANFGlobalsParserException("\"vert_path\" attribute not found.");
            
            Globals::getInstance().setShadingSettings(new ShadingSettings(_basePath + std::string(fp), _basePath + std::string(vp)));
        
        } else
            throw new ANFGlobalsParserException("Found an unexpected entry \"" + std::string(global->Value()) + "\".");
    }
}
