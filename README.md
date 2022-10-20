# Image Steganography

Going over boring lectures uses energy! What?! Did you notice that if you take the first letter of each word in the first sentence, it spells “Go Blue!”? Probably not, as unless you are looking for that pattern, it doesn’t stand out as anything special. However, if the recipient knew what to look for, it is incredibly simple to obtain the intended message. This is call steganography, which means hiding data or information in the midst of otherwise unsuspicious data or information. Steganography can be used to transmit encoded messages to a recipient without the need for ciphers, and this can be a benefit because an onlooker might not even recognize it as a secret message at all, meaning they wouldn’t know to try to “decode” it. 

## Background
Digital images happen to be a fantastic means to support the use of steganography, as most humans just look at the colors represented by the large array of pixel values and their brain interprets an image. Digital image is made up of many small pieces of data, and when managed in specific ways, can easily have information encoded within that data that virtually makes no difference to the image that the human eye sees.

In this project, I utilized the knowledge of file input/output and object-oriented programming and implement a steganography technique allowing us to “encode” messages into an image, such that the modified image could be sent to a friend, or posted on a social media site, and would likely only be able to be decoded by someone who knows it contains a hidden message.

### Some notes for .ppm imagery
PPM imagery unlike most other formats, are stored in an ASCII text file. More complicated image formats (like .gif and .jpg) are stored in a binary file and use sophisticated compression algorithms to make the file size smaller. A .ppm image can contain the exact same quality of image as a .gif or .jpg, but it would likely be significantly larger in file size since no compression is used. Since reading and writing text files are relatively easy, the only additional information we need is the format of the .ppm file.

Most image types start with two special characters, which are referred to as that image type's "magic number". A computer program can determine which type of image it is based on the value of these first two characters. For a .ppm image, the magic number is "P3", which simply allows an image viewing program to determine that this file is a PPM image and should be read using the PPM format.

Since a 100 pixel image may be an image of 25 rows and 4 columns, or 10 rows and 10 columns (or any other such combination) you need to know the specific size of the image. Therefore, after the magic number, the next two elements of the .ppm file are the width of the image, followed by the height of the image. Obviously, both of these values should be integers, since they both are in units of "number of pixels". (note: width (i.e. number of columns) comes first, and height (i.e. number of rows) comes second.)

The next value is also an integer, and is simply the maximum value in the color descriptions. For this project, I used 255 as the maximum number. With a maximum of 10, we are only allowed 10 shades of gray, and 10<sup>3</sup> unique colors which would not allow you to generate a very photographic looking image, but if your maximum value is 255, you could get a much wider range of colors (255<sup>3</sup>).

The only thing left is a description of each and every pixel in the image. The pixel in the upper left corner of the image comes first. The rest of the first row of pixels follows, and then the first pixel of the second row comes after that. This pattern continues until every pixel has been described (in other words, there should be rows\*cols pixel descriptions in the .ppm file). Each pixel is described with three integers (red, green, blue), so a 4 row by 4 column color image requires 4\*4\*3 = 48 integers to describe the pixels.

A very small image of a red square on a blue background would be stored in a .ppm file as follows:
```
P3
4 4
255
0 0 255   0 0 255   0 0 255   0 0 255
0 0 255   255 0 0   255 0 0   0 0 255
0 0 255   255 0 0   255 0 0   0 0 255
0 0 255   0 0 255   0 0 255   0 0 255
```

## Discription
As mentioned earlier, the steganography approach in this project will encode secret data within the pixel data of an otherwise uninteresting image. Humans are not very good at detecting tiny differences in color – for example, the full red RGB of (255, 0, 0) is essentially not distinguishable from the almost-full red RGB of (254, 1, 1). Therefore, we can make tiny modifications to colors and a human will not be able to detect the differences.

We will exploit this fact by modifying a portion of an image such that whether the individual RGB components are even or odd implies different colors. This limits us to being able to encode only 8 different colors, as described here:

* Encoding value: 0, Color description: Black, Encoding RGB: (Even, Even, Even)
* Encoding value: 1, Color description: Red, Encoding RGB: (Odd, Even, Even)
* Encoding value: 2, Color description: Green, Encoding RGB: (Even, Odd, Even)
* Encoding value: 3, Color description: Blue, Encoding RGB: (Even, Even, Odd)
* Encoding value: 4, Color description: White, Encoding RGB: (Odd, Odd, Odd)
* Encoding value: 5, Color description: Yellow, Encoding RGB: (Odd, Odd, Even)
* Encoding value: 6, Color description: Magenta, Encoding RGB: (Odd, Even, Odd)
* Encoding value: 7, Color description: Cyan, Encoding RGB: (Even, Odd, Odd)

Its important to realize that we aren’t just changing pixel values to the specified “encoding value”, because that would likely be very noticeable in the image. Instead, we are going to tweak the RGB components of a pixel by at most 1, which will be undetectable. Here’s how it will work – let’s say the current pixel value we’re going to encode is made up of RGB values of (108, 217, 62). If we want to encode the color yellow into the pixel, we need (Odd, Odd, Even), so we modify the RGB values to be (109, 217, 62). Similarly, if we had wanted to encode the color green, we need (Even, Odd, Even) – if the original pixel value was (108, 217, 62), then no changes are needed, as it already represents the encoded color green. As a final example, if we wanted to encode the color magenta, we need (Odd, Even, Odd), and again starting with (108, 217, 62), we can see that all three color components need to be modified, resulting in (109, 216, 63).

Algorithmically, here is the description: If a color attribute is even and we need to encode even, or it is odd and we need to encode odd, then no change to the value is made. If a color is odd and we need to encode even, then we simply subtract one from its value. Finally, if a color is even, and we need to encode odd, then we add one to its value. Notice that we don’t need to worry about “special cases” at the boundaries with this algorithm, because we never subtract from an even number, so we’d never subtract from 0 (which would result in an invalid -1 color attribute), and we never add to an odd number, so we’d never add to 255 (which would result in an invalid 256 color attribute).

Decoding the message simply works in reverse. If an encoded pixel’s value is (Even, Odd, Even), then it would be decoded to green, meaning the RGB components would be set to (0, 255, 0). All of our decoded colors should be “full colors”, meaning they are made up of some combinations of only 0s and 255s. Something to note: there is no way for us to “undo” a decode operation. Once a pixel has been decoded, its original RGB values have been replaced with the decoded color RGBs.

A very simple example here demonstrates the working principle:
![description](https://github.com/EricLiuuu/Image-Steganography/blob/main/Docs/description.PNG)
The message file describes the message that is to be encoded in an image. Its format is similar to the PPM in some ways, but since it is not actually a viewable image, there is no “magic number” in the file. The first field is the message’s width (number of columns first) and the second field is the message’s height (number of rows). Following that is a description of which color should be encoded for every “pixel” in the message. In the above example, we see the message is made up of 7s (cyan) and 1s (red). If you look at the message file, you should recognize that the message I want to encode is a cyan-colored “N” over a red background.

## Usage

To start the program, we need to provide the target .ppm file that we are going to work on. An image file called "deer.ppm" is used here for example.
```bash
bash-4.2$ ./project3.exe deer.ppm
```
If success, the terminal will display:
```
Reading initial image from: deer.ppm
Image read successful: Yes
1. Encode a message from file
2. Perform decode
3. Write current image to file
4. Exit the program
Enter your choice: 
```
There are four options on the interactive user panel:
1. Encoding: In this function, every pixel of the original picture will be modified according to the provided encoding message file. The encoding messages convert all different color rgb to eight different colors by distinguishing their parity. The whole image and the encoding message will be stored in different objects.

2. Decoding: In this function, the program operate the file in an opposite way. It takes the picture and convert all pixels into that eight colors by using the inversed encoding message. If there are some hidden messages in the picture, it will display clearly after decoding.

3. Writing to a file: This function will allow users to write the stored image to a ppm file. It include all necessary components of a ppm file.

4. Exit: Simply exit the program.

When encoding a message, the user will be prompted for which pixel in the original image the encoded message’s upper left corner should be placed at and an extra .txt file which contains the encoding information. Performing the decode operation does not require any additional inputs. When requesting to write the image to file in its current state, the user will be prompted to enter a file name to write the image to. Finally, when exiting the program, a “thank you” message is printed and the program ends.



## Acknowledgments

* [Morgan, Andrew](https://cse.engin.umich.edu/people/faculty/instructional-faculty/)

  Instructional faculty at University of Michigan - Ann Arbor, department of EECS
