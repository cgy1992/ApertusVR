package org.apertusvr.vlftsample;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Choreographer;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;

import org.apertusvr.ApertusJNI;
import org.apertusvr.apeEntity;
import org.apertusvr.apeNode;
import org.apertusvr.apeSceneNetwork;
import org.apertusvr.apeSceneManager;
import org.apertusvr.apeVector3;
import org.apertusvr.render.apeFilamentRenderPlugin;
import org.apertusvr.apeCoreConfig;
import org.apertusvr.apeMaterial;
import org.apertusvr.apeColor;
import org.apertusvr.apeManualMaterial;
import org.apertusvr.apeConeGeometry;
import org.apertusvr.apeVector2;

import java.util.Objects;
import java.util.concurrent.TimeUnit;

public class GameActivity extends AppCompatActivity {

    private static final String LOG_TAG = "javalog.GameActivity";

    Choreographer choreographer;
    private FrameCallback frameCallback = new FrameCallback();


    /* rendering */
    private apeFilamentRenderPlugin renderPlugin;
    private SurfaceView surfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Objects.requireNonNull(getSupportActionBar()).hide();

        setContentView(R.layout.activity_game);
        choreographer = Choreographer.getInstance();
        surfaceView = new SurfaceView(this);

        Intent intent = getIntent();
        String userName = intent.getStringExtra(MainActivity.EXTRA_USERNAME);
        String roomName = intent.getStringExtra(MainActivity.EXTRA_ROOMNAME);


        if (!MainActivity.apeStarted) {
            ApertusJNI apeJNI = new ApertusJNI();
            apeJNI.startApertusVR("vlftGuest",getAssets());
            MainActivity.apeStarted = true;
        }

        assert userName != null;
        createUserAvatar(userName);

        apeSceneNetwork.connectToRoom(roomName);

        setContentView(surfaceView);
        initRenderPlugin();
    }

    @Override
    public void onBackPressed() {
        //super.onBackPressed();
    }

    private void initRenderPlugin() {
        renderPlugin = new apeFilamentRenderPlugin(
                this, getLifecycle(), surfaceView,
                getResources(), getAssets());
        getLifecycle().addObserver(renderPlugin);
    }

    private apeNode createUserAvatar(String userName) {

        if(userName.length() > 0) {
            String GUID = apeCoreConfig.getNetworkGUID();
            apeNode userNode = apeSceneManager.createNode(
                    userName + "_" + GUID, true, GUID);
            if (userNode != null && userNode.isValid()) {

                userNode.setPosition(new apeVector3(0f, 150f, 150f));

                apeManualMaterial userMaterial = (apeManualMaterial) apeSceneManager.createEntity(
                        userName + "_" + GUID + "_Material",
                        apeEntity.Type.MATERIAL_MANUAL,
                        true, GUID);

                if(userMaterial != null && userMaterial.isValid()) {
                    apeColor color = new apeColor(
                            (float) Math.random(),
                            (float) Math.random(),
                            (float) Math.random());

                    userMaterial.setDiffuseColor(color);
                    userMaterial.setSpecularColor(color);

                    apeNode userConeNode = apeSceneManager.createNode(
                            userName + "_" + GUID + "_ConeNode", true, GUID);

                    if (userConeNode != null && userConeNode.isValid()) {
                        userConeNode.setParentNode(userNode);
                        userConeNode.rotate(90.0f, apeVector3.RIGHT, apeNode.TransformationSpace.WORLD);

                        apeConeGeometry userCone = (apeConeGeometry) apeSceneManager.createEntity(
                                userName + "_" + GUID + "_ConeGeometry",
                                apeEntity.Type.GEOMETRY_CONE,
                                true, GUID);

                        if (userCone != null && userCone.isValid()) {
                            userCone.setParameters(10.0f,30.0f, 1.0f, apeVector2.ONE);
                            userCone.setParentNode(userConeNode);
                            userCone.setMaterial(userMaterial);
                        }
                    }


                }
            }
        }
        return null;
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onResume() {
        super.onResume();
        choreographer.postFrameCallback(frameCallback);
    }

    @Override
    protected void onPause() {
        super.onPause();
        choreographer.removeFrameCallback(frameCallback);
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        choreographer.removeFrameCallback(frameCallback);

        if(MainActivity.apeStarted) {
            // TODO: ...
            Log.d(LOG_TAG,"STOP APEVR");
            ApertusJNI apeJNI = new ApertusJNI();
            apeJNI.stopApertusVR();
            MainActivity.apeStarted = false;
        }

        // finish();
    }

    class FrameCallback implements Choreographer.FrameCallback {
        @Override
        public void doFrame(long frameTimeNanos) {
            choreographer.postFrameCallback(this);
            ApertusJNI.processEventDoubleQueue();
        }
    }
}