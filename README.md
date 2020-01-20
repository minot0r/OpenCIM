# Open C Image Manipulation (OpenCIM)
Open C Image Manipulation is a lightweight image manipulation tool written C. Handles only bitmap files. for the moment 😄

## Installation

I'm using my favorite C compiler which is gcc 🥰. But you can compile on whatever you want
Just replace the `CC` flag in the makefile and then run :

```bash
make all
```

It will compile a dynamic library and place it into `libs` folder.

## Documentation

### Open Image (BMP)

```c
/* Calling open will give you a bm_file pointer
 * It contains info objects about file headers (image and file)
 * It also contains a pointer to the file stream
 * source here : https://github.com/minot0r/OpenCIM/blob/e77ccd6cdf2a363041f61ccf91c595fe282224e6/headers/cim.h#L41-L45
 */
bm_file* file = open("path/to/your/file.bmp");
```

### Print headers info (BMP)

```c
/* File header */
display_bm_fh(file->file_header);
/* Image header */
display_bm_ih(file->image_header);
```

### Paint image (BMP)

```c
/* This function has 3 parameters :
 * 1. A bm_file pointer
 * 2. A path to the output file
 * 3. A pointer to one of the function manipulation pixels of the image,
 * such as : invert, grayscale... etc
 */
paint(file, "path/to/output/file.bmp", a_pointer_to_func);
```

### Close Image (BMP)

```c
/* Don't forget to close the file, it will free memory, and
 * close the file stream
 */
close(file);
```