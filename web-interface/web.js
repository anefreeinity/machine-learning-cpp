// Get the input element and canvas
const input = document.getElementById("imageInput");
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

// Listen for changes in the input element
input.addEventListener("change", () => {
  const file = input.files[0];
  const reader = new FileReader();

  // Load the image file
  reader.onload = (e) => {
    const img = new Image();
    img.onload = () => {
      // Set the canvas size to 128x128 pixels
      let size = 720;
      canvas.width = size;
      canvas.height = size;

      // Draw the image on the canvas with resizing
      ctx.drawImage(img, 0, 0, img.width, img.height, 0, 0, size, size);

      // Get the image data
      const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
      const data = imageData.data;

      // Convert the image to black and white
      for (let i = 0; i < data.length; i += 4) {
        // Calculate grayscale value (average of RGB channels)
        const avg = (data[i] + data[i + 1] + data[i + 2]) / 3;

        // Set the RGB channels to the grayscale value
        data[i] = avg; // Red channel
        data[i + 1] = avg; // Green channel
        data[i + 2] = avg; // Blue channel
        // Set the alpha channel to 255 (fully opaque)
        data[i + 3] = 255;
      }

      // Update the image data on the canvas
      ctx.putImageData(imageData, 0, 0);

      // Log the pixel values to the console
      for (let i = 0; i < data.length; i += 4) {
        const grayValue = data[i]; // Use the red channel as the grayscale value
        if (grayValue > 50 && grayValue < 150) {
          console.log(`Pixel ${i / 4}: Value=${grayValue}`);
        }
      }
    };
    img.src = e.target.result;
  };
  reader.readAsDataURL(file);
});
