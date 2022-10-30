对于聚光灯模型，有几个重要的分量。‘
一个是切光角φ，还有就是聚光灯的位置position，以及聚光灯的朝向direction
lightingShader.setVec3("light.position",  camera.Position);
lightingShader.setVec3("light.direction", camera.Front);
lightingShader.setFloat("light.cutOff",   glm::cos(glm::radians(12.5f)));
这部分不太理解。到底front是什么？

还是要花些时间在照相机系统上。