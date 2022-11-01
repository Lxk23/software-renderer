# software-renderer
This is a simple software renderer written in c++ that implements our own graphics pipeline.
## 此光栅化软件渲染器使用c++语言进行编程，自己实现了图形学中的管线，进行模型的渲染。核心内容如下：
### 1.基于布雷森汉姆直线绘制算法绘制最基本图元——三角形
Bresenham布雷森汉姆直线绘制算法绘制线段，绘制三角形：把三角形分为上下两个部分，从下往上绘制三角形的边，同时找到三角形边上的像素，两个像素之间绘制线段填充三角形内部；
将三角形图元投影到屏幕上，进行像素的绘制：类似光栅化的方法绘制三角形，找到三角形的方形包围盒，遍历包围盒的内部的全部像素，，判断像素是否在三角形的内部：用叉积的方法。
![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/%E7%BB%98%E5%88%B6%E4%B8%89%E8%A7%92%E5%BD%A2.jpg)
### 2.zbuffer深度测试提升光栅化效率
深度测试：z buffer。在光栅化阶段完成：用zbuffer存储一个像素点(x,y)的深度信息（不同于图形管线）在三角形遍历时，若该像素在是三角形内部时开启深度测试：当该像素深度值大于zbuffer中存储的深度值时，丢弃该像素；当该像素深度值小于zbuffer中存储的深度值时，更新zbuffer深度值。
### 3.MVP矩阵变换
mvp变换：空间中物体本身在其模型空间中，我们需要在相机空间中进行渲染后投到屏幕空间中显示。所以要通过模型变换将物体从模型空间中变换到世界坐标系，通过视图变换将物体从世界坐标系变换到观察坐标系，通过透视投影矩阵将物体从相机空间中转换到裁剪空间，再从齐次坐标转换到非齐次坐标ndc，再乘以视口变换变到屏幕空间中。
### 4.高洛德着色模型
高洛德着色：逐顶点对光照进行计算，然后使用重心坐标对三角形内部的像素进行插值计算颜色。漫反射光模型采用Lambert光照模型，符合Lambert定律：在平面上某点漫反射光的光强与该反射点的法向量和入射光角度的余弦值成正比。
![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/Gouraud%E7%9D%80%E8%89%B2.jpg)
### 5.Phong着色模型
Phong着色：逐像素对光照进行计算，通过插值顶点的信息得到像素的各项信息。漫反射光+环境光+镜面光组成像素最后的颜色。环境光为一定值，漫反射光模型采用half Lambert光照模型，镜面光为Phong光照模型。  

![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/Phong%E7%9D%80%E8%89%B2.jpg)
#### 下面为多个obj模型（人头个眼睛）组合的效果图：
![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/%E5%A4%9A%E4%B8%AAobj%E5%90%88%E5%B9%B6.jpg)
### 6. 两个pass渲染实现硬阴影效果
硬阴影的实现：利用shadow map通过两个pass渲染实现。第一个pass将相机放在光源吗的位置来渲染，会将每个像素的深度记录在shadow map中，在第二个pass时，将相机放在原始位置，对于下渲染得到的像素，如果它在以光源位置为相机位置的深度大于shadow map中存储的深度则添加阴影，否则不需要添加阴影。
![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/shadowmap%E7%A1%AC%E9%98%B4%E5%BD%B1.jpg)
![image](https://github.com/Lxkaaaaaa/software-renderer/blob/picture/%E7%A1%AC%E9%98%B4%E5%BD%B1%E6%95%88%E6%9E%9C.jpg)
