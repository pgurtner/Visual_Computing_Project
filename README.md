# task
* capture a live camera stream using OpenCV
* use appropriate camera calibration parameters
* detect and track a known physical target
* estimate the target/camera pose using the techniques developed in Assignment 2
* transfer the estimated pose into the OpenGL rendering pipeline
* render virtual 3D content using your own OpenGL renderer
* display the camera image as the background of the OpenGL application
* correctly align the virtual content with the tracked physical target
* update the virtual content continuously as the camera or target moves

## pipeline
Camera Image

→ Target Detection / Tracking

→ Pose Estimation

→ Coordinate-System Conversion

→ OpenGL View / Projection

→ 3D Rendering

→ Augmented Reality View

A central part of the project is correctly handling the coordinate systems and conventions used by OpenCV and OpenGL.

# plan
we don't have to display the reference image right? Then we can avoid the tedious image concatenation.

## code structure
* while not closed:
  * draw webcam:
    * capture live webcam
    * render webcam
  * draw geometry:
    * detect and track target
    * estimate pose
    * coordinate system conversion
    * coordinate projection
    * render geometry

## todo
1. measure checkerboard tile sizes :/
2. finish Printer classes
3. add feature stuff to GeometryPrinter
4. move implementations of Printer class into .cpp files
5. look at new requirements

## schnickschnack
* versuchen Handy als Kamera zu nehmen, weil Webcam schon sehr eingeschränkt ist. V. a. bzgl. der Distanz: https://www.geeksforgeeks.org/python/connect-your-android-phone-camera-to-opencv-python/, 
* Pokémon
* z. B. auf Pokémon-Karten Pokémon abbilden, das hätte auch bisschen was über simples arbeiten nach Vorschrift hinaus
* als simplere Version auch das von Pokédex 3d pro glaube ich mit den checkerboard-like Bildercodes