# CS450 - Final Project

## Sun-Earth-Moon

#### Make
Compile project using Makefile. Default 'make' will build the project and object files. Add additional .cpp files at the top of the Makefile by appending with `SRC += [filename].cpp`.

```
make          # Builds executable
make run      # Builds executable and runs program
make clean    # Removes object files and project executable
make debug    # Adds Valgrind flags
make zip      # Zips project and all .cpp and .hpp files
```


#### Run
```
./project-7
```

## Description
![](data/img/sun-earth-moon.jpg)
<br>
A project showing the relationship between the Sun, Earth, and Moon using an exaggeration of 
real-world data while maintaining key proportions. There will be at least three views accessible with hotkeys and/or menu options, as outlined below. All bodies will be textured, lit and follow Kepler’s Third Law of Planetary Motion. Optionally, a user may increase or decrease animation speed by pressing the up or down arrows.


## Criteria

### Key areas to exaggerate:

1. Planet/Sun diameter (proportionate, with the possible exception of the sun)
2. Orbital radius (proportionate, with the possible exception of the earth to make it “tighter”)
3. Orbital speed (proportionate to orbital radius - Kepler’s Third Law)
4. Circular orbits

### Views:

1. Overall view - where the viewer can see everything.
2. Earth View - Where the eye is somewhere on the Earth, looking somewhere interesting.
3. Moon View - Where the eye is somewhere on the Moon, looking somewhere interesting.
4. Sun View (optional) - Where the eye is somewhere on the Sun, looking somewhere interesting.

### Physics

1. Kepler's Third law of planetary motion:
   Orbital Period is proportional to OrbitalRadius<sup>3/2</sup> = pow( OrbitalRadius, 3./2. )

## Data
**Sun** [(Wiki)](https://en.wikipedia.org/wiki/Sun):  
&emsp; diameter: 1.39 million km (864,000 miles)  
&emsp; radius: 696,342 km (432,687 miles)

**Earth** [(Wiki)](https://en.wikipedia.org/wiki/Earth):  
&emsp; radius: 6,371 km (3,958.8 miles)  

**Moon** [(Wiki)](https://en.wikipedia.org/wiki/Moon):  
&emsp; radius: 1,737.4 km (1,079.6 miles)


**Earth's Orbit** [(Wiki)](https://en.wikipedia.org/wiki/Earth%27s_orbit): 
&emsp; diameter: 149.60 million km (92.96 million miles)  
&emsp; time: 365.256 days  
&emsp; circumference: 940 million km (584 million miles)  
&emsp; orbital speed: 29.78 km/s (107,208 km/h; 66,616 mph)  
&emsp; equatorial plane (axis): 23.44º  
&emsp; **direction:** counter-clockwise

**Moon's Orbit** [(Wiki)](https://en.wikipedia.org/wiki/Orbit_of_the_Moon):  
&emsp; **diameter:** 385,000 km (239,000 miles) from Earth's center  
&emsp; **time:** 27.32 days (relative to stars)  
&emsp; **circumference:** 940 million km (584 million miles)  
&emsp; **orbital speed:** 1.022 km/s (0.635 miles/s)  
&emsp; **equatorial plane (axis):** 1.54º  
&emsp; **orbital plane (relative to ecliptic plane):** 5.14º  
&emsp; **direction:** counter-clockwise  
![](data/img/Lunar_Orbit_and_Orientation_with_respect_to_the_Ecliptic.png)

### Textures
Nasa Resources: [https://svs.gsfc.nasa.gov/](https://svs.gsfc.nasa.gov/)   
Nasa 3D Images: [https://nasa3d.arc.nasa.gov/images](https://nasa3d.arc.nasa.gov/images)  
CGI Moon Kit: [https://svs.gsfc.nasa.gov/4720](https://svs.gsfc.nasa.gov/4720)   
Solar System Textures: [https://www.solarsystemscope.com/textures/](https://www.solarsystemscope.com/textures/)

## Turn-in:

Use the [Teach system](http://engr.oregonstate.edu/teach) to turn in your:

1. Your .cpp file
2. A one-page PDF with a title, your name, your email address, a nice screen shot from your program, and the link to the Kaltura video demonstrating that your project does what the requirements ask for. Narrate your video so that you can tell us what it is doing.


## Grading:


| Item                                  | Points |
| --------------------------------------| ------ |
| Final Project Proposal                |   10   |
| Final Project                         |   40   |
| **Total**                             | **100**|
