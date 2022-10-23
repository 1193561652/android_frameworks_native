/*
 * Copyright 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <log/log.h>
#include "GLExtTexture.h"
#include "BatBitmap.h"
namespace android {
namespace renderengine {
namespace gl {

GLExtTexture::GLExtTexture() {
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &mName);
    glBindTexture(GL_TEXTURE_2D, mName);
    mTexture.init(Texture::TEXTURE_2D, mName);
    mTexture.setFiltering(true);
}

GLExtTexture::~GLExtTexture() {
    glDeleteTextures(1, &mName);
}

bool GLExtTexture::reload(int index) {
    // static uint8_t* data = new uint8_t[640*480*4];

    char filename[256] = {0};
    // index -= (index%10);
    snprintf(filename, sizeof(filename)-1, "/data/batman/%d.bmp", index);
    // int fd = open(filename, O_RDWR);
    // if (fd >= 0) {
    //     // ALOGE("BAT read file %s index:%d succ", filename, index);
    //     int readlen = read(fd, data, 640 * 480 * 4);
    //     if (readlen != 640 * 480 * 4) {
    //         ALOGE("BAT read file %s readlen:%d", filename, readlen);
    //     }
    //     close(fd);
    // } else {
    //     ALOGE("BAT open file %s error %d", filename, errno);
    // }

    static BatBitmap bmp;
    bmp.loadBitmap(filename);

    
    // for (int r=0; r < 480; r++) {
    //     for (int c=0; c < 640; c++) {
    //         int i = (r * 640 + c) * 4;
    //         data[i] = 0;
    //         data[i+1] = 0;
    //         data[i+2] = 0;
    //         if (r >= 480/2)
    //             data[i+3] = 255;
    //         else
    //             data[i+3] = 0;
    //     }
    // }

    glActiveTexture(GL_TEXTURE1);
    
    glBindTexture(GL_TEXTURE_2D, mName);
    glTexImage2D(GL_TEXTURE_2D, 0 /* base image level */, GL_RGB, bmp.getWidth(), bmp.getHeight(), 0 /* border */, GL_RGB, GL_UNSIGNED_BYTE, bmp.getByte());

    return true;
}

const Texture& GLExtTexture::getTexture() {
    return mTexture;
}

} // namespace gl
} // namespace renderengine
} // namespace android
