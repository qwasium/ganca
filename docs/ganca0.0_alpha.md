# ganca 0.0 alpha release documentation

- Jan. 24, 2024
- qwasium

## Introduction

Ganca is a eye-tracking data analysis software.

This is the first release of ganca. It is still in alpha stage, so it is not meant for production use.

For this release, I have restricted the platform and language as the following:

- Platform: Linux x86_64
- Language: Python 3.6 or higher

These "should work" but not tested. Development is done on Ubuntu 22.04 and Python 3.10.12.

Examples can be found in `/python_test` in the [git repository](https://github.com/qwasium/ganca).

## installation

The release is distributed as wheel package. You can install it with pip.

```bash

pip install /...path_to.../ganca-0.0.1a0-py3-none-any.whl

```

## `ganca`

### `ganca.aoihit.pyAOIHit`

Evaluate fixations if they are in the AOI.

```python
collision = ganca.aoihit.pyAOIHit.cntRasterAOI(
    aoiMask,
    fixX,
    fixY,
    winX,
    winY
)
```

Parameters

- `aoiMask`: 2D array (list of list or tuple of tuple)
  - (x, y) matrix of AOI mask that matches the resolution of the screen.
  - 1 if the pixel is in the AOI, 0 otherwise.
- `fixX`: list or tuple
  - x coordinate of fixations.
  - must be in display pixel.
- `fixY`: list or tuple
  - y coordinate of fixations.
  - must be in display pixel.
- `winX`: int
  - resolution x of the screen.
  - length of the first dimension of `aoiMask`.
- `winY`: int
  - resolution y of the screen.
  - length of the second dimension of `aoiMask`.

Returns

- `collision`: tuple of bool
  - True if the fixation is in the AOI, False otherwise.


### `ganca.fixationfilter.pyFixationFilter`

#### `ganca.fixationfilter.pyFixationFilter.FixationFilter`

Fixation filter class.

Only a simplified sigle eye only I-VT filter is implemented. The current implementation is only for testing and evaluation purposes and only 2 sequencial data points are evaluated for fixation identification. The following features are not implemented and should not be used for production.

- signal processing such as low-pass filter
- noise reduction such as moving average
- detecting system related missig data and gap filling/interpolation
- binocular data processing and eye selection
- treatment of close proximity fixations
- treatment of short fixations
- output of fixation table with fixation start, fixation end, fication duration and fixation coordinates

##### Attributes

`FixationFilter.timestamp`: list/tuple of float

- Timestamps of the gaze data, UNIX time, can be eyetracker timestamp or system timestamp

`FixationFilter.validityIn`: list/tuple of bool

- Validity of the gaze data, True if valid, False otherwise

`FixationFilter.gazeVectorX`: list/tuple of float

- Gaze vector x
- for Tobii: gaze point x(ucs) - gaze origin x(ucs)

`FixationFilter.gazeVectorY`: list/tuple of float

- Gaze vector y
- for Tobii: gaze point y(ucs) - gaze origin y(ucs)

`FixationFilter.gazeVectorZ`: list/tuple of float

- Gaze vector z
- for Tobii: gaze point z(ucs) - gaze origin z(ucs)

`FixationFilter.velocityThreshold`: float

- Velocity threshold for fixation identification
- Tobii IV-T default: 30 deg/s

`FixationFilter.isFixation`: list/tuple of bool

- True if fixation, False otherwise
- each element is an evaluation between two sequencial data points
- length is `len(timestamp) - 1`

`FixationFilter.validityOut`: list/tuple of bool

- Validity of the fixation data, True if valid, False otherwise
- each element is an evaluation between two sequencial data points
- length is `len(timestamp) - 1`

`FixationFilter.velocity`: list/tuple of float

- Velocity of the gaze data in deg/s
- each element is an evaluation between two sequencial data points
- length is `len(timestamp) - 1`

`FixationFilter.timestampOut`: list/tuple of float

- Timestamps of the fixation data, UNIX time, can be eyetracker timestamp or system timestamp
- each element is the average between two sequencial data points
- length is `len(timestamp) - 1`


##### constructor

```python
ganca.fixationfilter.pyFixationFilter.FixationFilter(
    timestampInInit,
    validityInInit,
    gazeVectorXInit,
    gazeVectorYInit,
    gazeVectorZInit,
)
```

Parameters

- `timestampInInit`: list/tuple of float
  - Initialize `FixationFilter.timestamp`
- `validityInInit`: list/tuple of bool
  - Initialize `FixationFilter.validityIn`
- `gazeVectorXInit`: list/tuple of float
  - Initialize `FixationFilter.gazeVectorX`
- `gazeVectorYInit`: list/tuple of floaT
  - Initialize `FixationFilter.gazeVectorY`
- `gazeVectorZInit`: list/tuple of float
  - Initialize `FixationFilter.gazeVectorZ`

##### Methods

I-VT filter

```python
None = ganca.fixationfilter.pyFixationFilter.FixationFilter.IVTfilter(
    velocityThreshold
)
```

Apply I-VT filter to gaze vector attributes and output the results to the attributes `FixationFilter.isFixation`, `FixationFilter.validityOut`, `FixationFilter.velocity` and `FixationFilter.timestampOut`.

Parameters

- `velocityThreshold`: float
  - Initialize `FixationFilter.velocityThreshold`

##### Example

```python

from ganca.fixationfilter import pyFixationFilter

# data values are meaningless. just for example.
time_stamp = (0.0, 0.1, 0.2, 0.3, 0.4, 0.5) # tuple of timestamp
validity = (True, True, True, True, True, True) # tuple of data validity
gaze_vector_x = (0.0, 0.1, 0.2, 0.3, 0.4, 0.5) # tuple of gaze vector x
gaze_vector_y = (0.0, 0.1, 0.2, 0.3, 0.4, 0.5) # tuple of gaze vector y
gaze_vector_z = (0.0, 0.1, 0.2, 0.3, 0.4, 0.5) # tuple of gaze vector z

# initialize
fix_filter = pyFixationFilter.FixationFilter(
    timestampInInit = time_stamp,
    validityInInit = validity,
    gazeVectorXInit = gaze_vector_x,
    gazeVectorYInit = gaze_vector_y,
    gazeVectorZInit = gaze_vector_z
)

# apply I-VT filter
fix_filter.IVTfilter(
    velocityThreshold = 30.0
)

# read the results
# the attributes are swig pointer objects, so convert to list or tuple to print
print(list(fix_filter.isFixation))
print(list(fix_filter.validityOut))
print(list(fix_filter.velocity))
print(list(fix_filter.timestampOut))

```

### `ganca.heatmap.pyHeatmap`

Create heatmap from fixation data.

This will only create a matrix of raw values using gauss sum. You need to use other software to visualize the heatmap.

To use kernel density estimation with Gaussian kernel, set `fixDur` to a list of equal values and control the weight by the number of elements in `fixX` and `fixY`.

```python
heat_map = ganca.heatmap.pyHeatmap.heatmapGauss(
    fixX,
    fixY,
    fixDur,
    winX,
    winY,
    sigma_factor
)
```

Parameters

- `fixX`: list or tuple
  - x coordinate of fixations.
  - must be in display pixel.
- `fixY`: list or tuple
  - y coordinate of fixations.
  - must be in display pixel.
- `fixDur`: list or tuple
  - duration of fixations.
  - set to a list of equal values to use kernel density estimation with Gaussian kernel.
- `winX`: int
  - resolution x of the screen.
- `winY`: int
  - resolution y of the screen.
- `sigma_factor`: float
  - sigma factor for gauss sum.
  - there is no guideline for this value. you need to test and find the best value for your data.

Returns

- `heat_map`: tuple of tuple of float
  - (x, y) matrix of heatmap.
  - the value is the value of the gauss-sum distribution at the pixel

### `ganca.helper.pyHelper`

helper functions

```python
coord_pixel = ganca.helper.pyHelper.displayAreaToPixels(
    coordsAbs,
    resolution
)
```

Active Display Cordinate System(ADCS) to pixel coordinates. ADCS sets the origin at the top left corner of the display and (1, 1) is the bottom right corner display.

This function will take a one-dimentional array of the gaze point coordinates in ADCS and convert them to pixel coordinates on the display.


Parameters

- `coordsAbs`: list or tuple of float
  - array of gaze point data in ADCS
  - one-dimentional, x or y and right or left only at a time
- `resolution`: tuple of int
  - corresponding resolution of the display


