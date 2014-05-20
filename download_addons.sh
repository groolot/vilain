#!/bin/bash

INSTALL_DIR=${HOME}/openframeworks/addons

# Get dependencies addons
if [ -d ${INSTALL_DIR} ]
then
    VILAIN_DEPENDENCIES=('ofxAnimatable' 'ofxAppUtils' 'ofxBlur' 'ofxCv' 'ofxCvOpticalFlowLK' 'ofxDirList' 'ofxDmx' 'ofxDraggable' 'ofxFenster' 'ofxFTGL' 'ofxImageSequence' 'ofxMSAInteractiveObject' 'ofxMSATimer' 'ofxMtlMapping2D' 'ofxNamedVariables' 'ofxOscRouter' 'ofxPlaylist' 'ofxPostProcessing' 'ofxProjectorBlend' 'ofxRange' 'ofxRenderManager' 'ofxTextInputField' 'ofxTextureServer' 'ofxTimecode' 'ofxTimeline' 'ofxTween' 'ofxUI' 'ofxVideoMapping' 'ofxWordPalette' )
    pushd ${INSTALL_DIR}
    for i in $(seq 0 $((${#VILAIN_DEPENDENCIES[@]} - 1)) )
    do
	git clone https://github.com/groolot/${VILAIN_DEPENDENCIES[i]}.git
    done
    popd
    exit 0
else
    echo "No AddOns have been installed due to absence of ${INSTALL_DIR}, required directory" >&2
    exit 1
fi

exit 1