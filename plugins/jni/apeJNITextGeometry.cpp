//
// Created by Erik on 2020. 08. 08..
//
#include "apeJNIPlugin.h"
#include "apeITextGeometry.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_setTextGeometryCaption(JNIEnv* env, jclass clazz, jstring native_text, jstring caption)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);
    const char* captionName = env->GetStringUTFChars(caption, nullptr);

    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->setCaption(captionName);
    }

    env->ReleaseStringUTFChars(native_text, name);
    env->ReleaseStringUTFChars(caption, captionName);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_org_apertusvr_ApertusJNI_getTextGeometryCaption(JNIEnv *env, jclass clazz, jstring native_text)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    const char* caption = jniPlugin->NA_STR;
    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        caption = textGeometryShared->getCaption().c_str();
    }

    env->ReleaseStringUTFChars(native_text, name);

    return env->NewStringUTF(caption);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_setTextGeometryParentNode(JNIEnv *env, jclass clazz, jstring native_text, jstring parent_node)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);
    const char* parentNodeName = env->GetStringUTFChars(parent_node, nullptr);

    auto parentNode = jniPlugin->getSceneManager()->getNode(std::string(parentNodeName));

    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->setParentNode(parentNode);
    }

    env->ReleaseStringUTFChars(native_text, name);
    env->ReleaseStringUTFChars(parent_node, parentNodeName);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_clearTextGeometryCaption(JNIEnv *env, jclass clazz, jstring native_text)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->clearCaption();
    }

    env->ReleaseStringUTFChars(native_text, name);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_apertusvr_ApertusJNI_isTextGeometryVisible(JNIEnv *env, jclass clazz, jstring native_text)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    bool visibility = false;
    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        visibility = textGeometryShared->isVisible();
    }

    env->ReleaseStringUTFChars(native_text, name);

    return (jboolean) visibility;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_setTextGeometryVisible(JNIEnv *env, jclass clazz, jstring native_text, jboolean enabled)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->setVisible(bool(enabled));
    }

    env->ReleaseStringUTFChars(native_text, name);

}

extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_showTextGeometryOnTop(JNIEnv *env, jclass clazz, jstring native_text, jboolean show)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->showOnTop(bool(enabled));
    }

    env->ReleaseStringUTFChars(native_text, name);

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_apertusvr_ApertusJNI_isTextGeometryShownOnTop(JNIEnv *env, jclass clazz, jstring native_text)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    bool shownOnTop = false;
    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        shownOnTop = textGeometryShared->isVisible();
    }

    env->ReleaseStringUTFChars(native_text, name);

    return (jboolean) shownOnTop;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_apertusvr_ApertusJNI_setTextGeometryOwner(JNIEnv *env, jclass clazz, jstring native_text, jstring owner_id)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);
    const char* ownerID = env->GetStringUTFChars(owner_id,nullptr);
    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        textGeometryShared->setOwner(std::string(ownerID));
    }

    env->ReleaseStringUTFChars(native_text, name);
    env->ReleaseStringUTFChars(owner_id, ownerID);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_org_apertusvr_ApertusJNI_getTextGeometryOwner(JNIEnv *env, jclass clazz, jstring native_text)
{
    ape::JNIPlugin* jniPlugin = ape::JNIPlugin::getPluginPtr();
    const char* name = env->GetStringUTFChars(native_text, nullptr);

    const char* ownerID = jniPlugin->NA_STR;
    if(auto textGeometryShared = std::static_pointer_cast<ape::ITextGeometry>(jniPlugin->getSceneManager()->getEntity(std::string(name)).lock()))
    {
        ownerID = textGeometryShared->getOwner().c_str();
    }

    env->ReleaseStringUTFChars(native_text, name);

    return env->NewStringUTF(ownerID);
}