# Mineclone - Voxel Game
**A simple Minecraft Clone written in C++ OpenGL and SDL2**

![preview_01.png](assets/images/preview_01.png)

## Build Instructions
### Prerequisites
- **SDL2**
- **GLEW**
- **freetype**

```
git clone https://github.com/vockers/mineclone.git
cd mineclone
make
./mineclone
```

## TODO
- **Infinite Height:** Implement support for generating world with infinite height.
- **Frustum Culling:** Optimize rendering using frustum culling.
- **World Serialization:** Save and load the game world to/from disk for persistence and saving RAM.
- **Breaking/Placing Blocks:** Updating chunks after left/right clicking blocks
- **Day-Night Cycle:** Implement a dynamic day-night cycle with block lighting data.
- **Physics:** Player gravity and collision with the world.