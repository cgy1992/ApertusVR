package org.apertusvr;

import androidx.annotation.Size;

public class apeTextGeometry extends apeGeometry {

    public apeTextGeometry(String name) {
        super(name, Type.GEOMETRY_TEXT);
    }

    public void setCaption(String caption) {
        ApertusJNI.setTextGeometryCaption(mName, caption);
    }

    public String getCaption() {
        return ApertusJNI.getTextGeometryCaption(mName);
    }

    public void clearCaption() {
        ApertusJNI.clearTextGeometryCaption(mName);
    }

    public boolean isVisible() {
        return ApertusJNI.isTextGeometryVisible(mName);
    }


    public void setVisible(boolean enabled) {
        ApertusJNI.setTextGeometryVisible(mName, enabled);
    }

    public void setParentNode(apeNode parentNode) {
        ApertusJNI.setTextGeometryParentNode(mName,parentNode.getName());
    }

    public void showOnTop(boolean show) {
        ApertusJNI.showTextGeometryOnTop(mName, show);
    }

    public boolean isShownOnTop() {
        return ApertusJNI.isTextGeometryShownOnTop(mName);
    }

    public void setOwner(String ownerID) {
        ApertusJNI.setTextGeometryOwner(mName,ownerID);
    }

    public String getOwner() {
        return ApertusJNI.getTextGeometryOwner(mName);
    }
}
