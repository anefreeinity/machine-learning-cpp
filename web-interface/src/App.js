import { useEffect, useState } from "react";
import "./App.css";
import AutoComplete, { toRoman } from "./component/Autocomplete";
import IMAGES from "./assets/image_data.json";
import DashBoard from "./component/DashBoard";
import { ThemeProvider, createTheme } from "@mui/material/styles";
import CssBaseline from "@mui/material/CssBaseline";

const darkTheme = createTheme({
  palette: {
    mode: "dark",
  },
});

function App() {
  const [windowWidth, setWindowWidth] = useState(window.innerWidth);
  const [windowHeight, setWindowHeight] = useState(window.innerHeight);
  const [images, setImages] = useState([]);
  const [currentSelectedImage, setCurrentSelectedImage] = useState(null);
  const [prediction, setPrediction] = useState(null);

  useEffect(() => {
    const handleResize = () => {
      setWindowWidth(window.innerWidth);
      setWindowHeight(window.innerHeight);
    };

    const fetchImages = () => {
      let imageObjs = IMAGES.map((image, i) => {
        let label = image.label || 0;
        return {
          id: `select ${label.toString()} from ${toRoman(
            i + 1
          )} place in MNIST dataset`,
          image: image.image,
          label: label.toString(),
        };
      });
      setImages(imageObjs);
    };

    fetchImages();
    window.addEventListener("resize", handleResize);

    return () => {
      window.removeEventListener("resize", handleResize);
    };
  }, []);

  return (
    <div className="relative bg-custom bg-opacity-50 w-screen">
      <div className="absolute inset-0 bg-gradient-to-b from-black to-transparent"></div>
      <div className="relative z-10">
        <h1 className="text-4xl font-bold text-white">ANEFreeInIty</h1>
      </div>
      <div className="z-10 relative">
        <ThemeProvider theme={darkTheme}>
          <CssBaseline />
          <AutoComplete
            width={windowWidth}
            height={windowHeight}
            images={images}
            setCurrentSelectedImage={setCurrentSelectedImage}
            setPrediction={setPrediction}
          />
        </ThemeProvider>
      </div>
      {currentSelectedImage && (
        <div className="z-10">
          <ThemeProvider theme={darkTheme}>
            <CssBaseline />
            <DashBoard
              width={windowWidth}
              height={windowHeight}
              selectedImage={currentSelectedImage}
              prediction={prediction}
              setPrediction={setPrediction}
            />
          </ThemeProvider>
        </div>
      )}
    </div>
  );
}

export default App;
