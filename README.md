# 2D Game Engine for QML

Bacon2D is a framework to ease 2D game development, providing ready-to-use QML 
components useful for creating compeling games.

API documentation can be found at [here](http://bacon2d.com/docs).

## 1. Build

### 1.1) Dependencies

* [Qt5](https://qt.gitorious.org/qt/qt5)

### 1.2) Building

Available QMake parameters:

* QTPATH (Optional)
	Prefix where Qt has been installed. It is required to install
	Bacon2D's QML import plugin and related files.
	The default path is /usr/lib/qt5


If building from a git checkout, you will need to initialize the git submodules:
 ```sh
$ git submodule update --init
```
Sample build from Bacon2D's root source tree:
 ```sh
$ mkdir build && cd build
$ qmake QTPATH=/opt/Qt5 ..
$ make
$ sudo make install
```

*MacOS note*:

If you get some error like 'could not resolve SDK path for...', add 
**'QMAKE_MAC_SDK=MAC_SDK_VERSION'** to the qmake command, like this (issue #80):
 ```sh
$ qmake QMAKE_MAC_SDK=macosx10.9 ..
```
Where **MAC_SDK_VERSION** points to the OSX version you're using (in the above 
example it is 10.9.x).

## 2. Examples

If you have installed the QML plugin to the proper Qt import directory,
you can run the examples directly from their specific source directories.

Each example can be opened and run from QtCreator, to open the fixtures 
example, open examples/fixtures/fixtures.qmlproject from QtCreator

To run the fixtures example without QtCreator:
 ```sh
$ cd examples/fixtures
$ qmlscene main.qml
```
If Bacon2D QML plugin was not installed you can export QML2_IMPORT_PATH 
environment variable or specify the path to your built plugin on 
the command line.
 ```sh
$ cd examples/fixtures
$ qmlscene -I ../../build/src/imports main.qml
```

## 3. Get Involved

[Contact us](http://bacon2d.com/contact.html)

## 4. Enhancements

* Customizable background for TiledScene class using any QQuickItem (overrides the Tiled image layer set in TMX file)
* More efficient spritesheet handling
* Easier to use sprite classes
* Added EntityManager class for managing all entities in a game
* Converted PhysicsEntity QML class to PhysicsEntity C++ class (as suggested by adderly)
* Added PausableTimer class, QML Timer with the ability to pause and resume at will
* Added SpriteSheet and SpriteStrip QML component
* Added TiledPropertyMapping for mapping properties in a TMX file to properties of a PhysicsEntity
* Added TiledImage for setting the properties of a Tiled image
* Added TiledObjectGroup for representing a TiledObjectGroup
* Swapped a parallel state machine for a sequential state machine for sprite animations, preventing parallel running sprite animations
* Added map property to TiledScene for setting background color etc. Also added TiledMap::getProperty() method to TiledScene "map" property to allow user to get properties from a TMX map
* Added VirtualJoystick
* Added GesturePad
* Added ButtonPad
* Introduced Android support
* Added Game::DeviceScreen for setting screen properties like properties for keep the orientation fixed and the screen powered on
* Added Scene::anchorItem for anchoring items to the display
* Added Entity::ViewportTracker for tracking entities within a viewport
* Added KeyInput and KeyAction for handling keyboard input

## 5. Bug fixes

* Sprites out of sync with their animations sometimes
* Multiple SpriteAnimation objects running at once

## 6. See also
* [Seppuku](https://github.com/obeezzy/Seppuku), game built with Bacon2D (far from complete)
