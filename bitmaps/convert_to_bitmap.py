import os
from PIL import Image
from string import Template

letter_template = Template(
"""
constexpr uint8_t letter_$letter[52] =
{
    $data
};
""")

def image_to_array(image_path):
    img = Image.open(image_path)
    if img.size != (13, 32):
        raise ValueError("Image must be 13 pixels wide and 32 pixels tall")
    binary_array = []
    for y in range(img.height):
        row = []
        for x in range(img.width):
            pixel = img.getpixel((x, y))
            binary_array.append(1 if pixel[3] == 255 else 0)
    return binary_array

files = os.listdir("bitmaps")

for file in files:
    if file.endswith(".png"):
        data = image_to_array("bitmaps/" + file)
        
        # chunks of 8
        data = [str(i) for i in data]
        data = [data[i:i+8] for i in range(0, len(data), 8)]

        bin_data = ""
        for chunk in data:
            bin_data += '0b' + ''.join(chunk) + ",\n    "
            
        print(letter_template.safe_substitute(dict(
            letter=file.split('.')[0],
            data=bin_data
        )))
            
        
        