import React, { useRef, useState, useEffect } from "react";

export default function DigitDrawing({
  width,
  height,
  prediction,
  setPrediction,
}) {
  let dashboardClass = "border-zinc-600";

  return (
    <div
      style={{
        width: (width * 3) / 5,
        margin: 0,
        position: "absolute",
        top: `${height / 2}px`,
        left: `${width / 2 - (width * 3) / 10}px`,
      }}
      className={`border z-10 bg-transparent text-white rounded ${dashboardClass}`}
    >
      <DrawOnCanvas
        width={200}
        height={200}
        outputWidth={28}
        outputHeight={28}
        prediction={prediction}
        setPrediction={setPrediction}
      />
    </div>
  );
}

async function predictDigit(selectedImage, setPrediction) {
  console.log("sending api request...");
  console.log(JSON.stringify(selectedImage));

  const URL = "http://127.0.0.1:5000/api/predict";
  const jsonData = JSON.stringify(selectedImage);
  fetch(URL, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: jsonData,
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error("Failed to fetch");
      }
      return response.json();
    })
    .then((data) => {
      console.log(data);
      setPrediction(String(data.predictedDigit));
    })
    .catch((error) => {
      console.error(error);
    });
}

export function DrawOnCanvas({
  width = 400,
  height = 400,
  outputWidth = 28,
  outputHeight = 28,
  prediction,
  setPrediction,
}) {
  const canvasRef = useRef(null);
  const [drawing, setDrawing] = useState(false);

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas.getContext("2d");

    const startDrawing = (e) => {
      setDrawing(true);
      draw(e);
    };

    const stopDrawing = () => {
      setDrawing(false);
      ctx.beginPath();
    };

    const draw = (e) => {
      if (!drawing) return;

      const rect = canvas.getBoundingClientRect();
      const x =
        (e.clientX ? e.clientX - rect.left : e.touches[0].clientX - rect.left) *
        (canvas.width / rect.width);
      const y =
        (e.clientY ? e.clientY - rect.top : e.touches[0].clientY - rect.top) *
        (canvas.height / rect.height);

      ctx.lineWidth = 20;
      ctx.lineCap = "round";
      ctx.strokeStyle = "#ffffff";

      ctx.lineTo(x, y);
      ctx.stroke();
      ctx.beginPath();
      ctx.moveTo(x, y);
    };

    canvas.addEventListener("mousedown", startDrawing);
    canvas.addEventListener("mouseup", stopDrawing);
    canvas.addEventListener("mousemove", draw);

    canvas.addEventListener("touchstart", startDrawing);
    canvas.addEventListener("touchend", stopDrawing);
    canvas.addEventListener("touchmove", draw);

    canvas.addEventListener("touchstart", (e) => e.preventDefault());
    canvas.addEventListener("touchmove", (e) => e.preventDefault());

    return () => {
      canvas.removeEventListener("mousedown", startDrawing);
      canvas.removeEventListener("mouseup", stopDrawing);
      canvas.removeEventListener("mousemove", draw);
      canvas.removeEventListener("touchstart", startDrawing);
      canvas.removeEventListener("touchend", stopDrawing);
      canvas.removeEventListener("touchmove", draw);
      canvas.removeEventListener("touchstart", (e) => e.preventDefault());
      canvas.removeEventListener("touchmove", (e) => e.preventDefault());
    };
  }, [drawing]);

  const getGrayscaleImageData = () => {
    const canvas = canvasRef.current;
    const offscreenCanvas = document.createElement("canvas");
    offscreenCanvas.width = outputWidth;
    offscreenCanvas.height = outputHeight;
    const offscreenCtx = offscreenCanvas.getContext("2d");

    offscreenCtx.clearRect(0, 0, offscreenCanvas.width, offscreenCanvas.height);

    offscreenCtx.drawImage(
      canvas,
      0,
      0,
      offscreenCanvas.width,
      offscreenCanvas.height
    );

    const imageData = offscreenCtx.getImageData(
      0,
      0,
      offscreenCanvas.width,
      offscreenCanvas.height
    );
    const data = imageData.data;
    const grayscaleData = [];

    for (let i = 0; i < data.length; i += 4) {
      const r = data[i];
      const g = data[i + 1];
      const b = data[i + 2];
      const a = data[i + 3];
      if (r || g || b || a) {
        console.log(`r = ${r}, g = ${g}, b = ${b}, a = ${a}`);
      }
      const grayscale = Math.round(0.299 * r + 0.587 * g + 0.114 * b);
      grayscaleData.push(grayscale);
    }

    return grayscaleData;
  };

  function handelPrediction() {
    const grayscaleData = getGrayscaleImageData();
    console.log(grayscaleData);
    console.log(grayscaleData.filter((a) => a > 0).length);
    predictDigit(grayscaleData, setPrediction);
  }

  return (
    <div className="flex p-4">
      <div className="w-1/2">
        <p className="pt-2">
          Predicted digit: {prediction ? prediction : "Draw to Predict"}
        </p>
        <button
          onClick={handelPrediction}
          className="absolute bottom-4 left-4 bg-transparent text-white font-semibold hover:text-white py-2 px-4 border border-zinc-600 hover:border-zinc-400 rounded"
        >
          Predict
        </button>
      </div>
      <div className="w-1/2 flex justify-end">
        <div>
          <canvas
            className="rounded border border-zinc-800"
            ref={canvasRef}
            width={width}
            height={height}
            style={{
              touchAction: "none",
              width: `${width}px`,
              height: `${height}px`,
              backgroundColor: "#000000",
              imageRendering: "pixelated",
            }}
          />
        </div>
      </div>
    </div>
  );
}
