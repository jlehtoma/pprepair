
## What is pprepair?

pprepair (*p*lanar *p*artition repair) takes a set of polygons and ensures that they form a valid planar partition, made of valid polygons and having no gaps or overlaps. 
It can be used as a validator, telling of problems in individual polygons or in the planar partition, and also as an automatic repair tool, outputting a set of polygons that do form a valid planar partition. 
If you are only interested in repairing individual polygons, have a look at [prepair](https://github.com/tudelft-gist/prepair).


## What is a planar partition and why is it important to have valid planar partitions?

Planar partitions are subdivisions of the plane into polygons, and are frequently used in GIS to model various concepts like land use, geology, administrative subdivisions, natural features and cadastral parcels, among many others.

However, the polygons in a planar partition are often created separately, and thus cannot be expected to fit with each other exactly. Other times, these polygons are stored and modified separately, causing different errors and inconsistencies to be introduced. These come in the form of invalid polygons, gaps, overlaps and disconnected polygons.

When software that expects a planar partition received one that is not so, it can give erroneous results (in the best case), or fail to give a result at all, often without a clear explanation to the user.

## How does pprepair work?

In short, pprepair creates a constrained triangulation of the polygons, tags each triangle with the polygon that it belongs to, modifies the triangulation to ensure that only one tag is present in each, and reconstructs the polygons from the triangulation. 

Many more details are available in Ken Arroyo Ohori's MSc thesis [here](http://www.gdmc.nl/ken/files/10_msc_thesis.pdf).

If you use pprepair for your research, please cite this publication:

> Arroyo Ohori, Ken, Ledoux, Hugo and Meijers, Martijn (2012). Validation and automatic repair of planar partitions using a constrained triangulation. *Photogrammetrie, Fernerkundung, Geoinformation (PFG)*. 5:613–630. [ [PDF] ](https://3d.bk.tudelft.nl/ken/files/12_pfg.pdf) [ [DOI] ](http://dx.doi.org/10.1127/1432-8364/2012/0143)

## How do I use pprepair?

pprepair is a command-line program, which we provide as source code. It is very easy to compile it on Linux and Mac. We plan on offering binaries (including for Windows) in the future.

To compile pprepair, you first need to install the free libraries [CGAL](http://www.cgal.org) and [GDAL](http://www.gdal.org). [CMake](http://www.cmake.org) is highly recommended. Under Mac, we recommend using [Homebrew](http://brew.sh/) to install CGAL (and all its dependencies) and CMake, and GDAL is easily installed with the framework installed of [KyngChaos](http://www.kyngchaos.com/software/frameworks#gdal_complete).

To install it, run:

    $ cmake .
    $ make

To see all the possible options:

    $ ./pprepair -h

To validate a file (test whether it forms a planar partition)
    
    $ ./pprepair -i file.shp -v

To validate 2 files:

    $ ./pprepair -i file.shp -i file2.shp -v

To validate 2 files and output the errors in a shapefile (in the current folder):

    $ ./pprepair -i file.shp -v --outerrors err.shp

To validate 2 files and output the triangulation (where each triangle has the number of labels the input contains):

    $ ./pprepair -i file.shp -v --outtr tr.shp

To repair with the simplest method (RandomNeighbour) the gaps/overlaps in a file, and output the result in the current directory (file `file.r.shp` will be created):

    $ ./pprepair -i file.shp -o . -r fix


To repair with the a PriorityList rule (file prio.txt)

    $ ./pprepair -i file.shp -o . -r PL --prio prio.txt

To repair with the simplest method and output the result in the current directory (file `file.r.shp` will be created):

    $ ./pprepair -i file.shp -o . -r fix


## Can I use pprepair in my organisation? What is the license of pprepair?

Following in CGAL's footsteps, pprepair is available under a dual license scheme, GPLv3 and commercial. 
If you choose to use pprepair under the free-of-charge GPLv3 license, you have to comply with its terms. 
If these are not suitable for you, you have to buy a commercial license.

The [GPLv3](http://www.gnu.org/copyleft/gpl.html) allows you to use, copy and modify the software freely. 
However, if you incorporate pprepair in your software, you must distribute the source code of your software, as well as any modifications made to pprepair, under the GPLv3 as well.

If you are interested in getting a commercial license for pprepair, please contact [Ken Arroyo Ohori](mailto:g.a.k.arroyoohori@tudelft.nl).

## Help! pprepair is crashing or giving weird results

If your problem persists, please report it [here](https://github.com/tudelft-gist/pprepair/issues?state=open).
