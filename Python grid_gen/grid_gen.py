
# coding: utf-8

# In[35]:


from PIL import Image, ImageDraw

step_count = 52
h = 800
w = 600
img = Image.new(mode="RGB", size=(h, w), color=(0, 0, 0))

draw = ImageDraw.Draw(img)
step_size = int(img.width / step_count)

y0 = 0
y1 = img.height
for x in range(0, img.width, step_size):
    line = ((x, y0), (x, y1))
    draw.line(line, fill=(123, 17, 237))

x0 = 0
x1 = img.width
for y in range(0, img.height, step_size):
    line = ((x0, y), (x1, y))
    draw.line(line, fill=(123, 17, 237))

image.show()


# In[36]:


image

