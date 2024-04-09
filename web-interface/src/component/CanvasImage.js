import { useEffect, useRef } from "react";

export default function CanvasImage({
  imageWidth,
  imageHeight,
  imageData,
  className,
}) {
  const canvasRef = useRef(null);
  const scale = imageWidth / 28;
  useEffect(() => {
    imageData && makePicture(canvasRef, imageData, scale);
  }, [imageData, scale]);

  return (
    <canvas
      className={className}
      ref={canvasRef}
      width={imageWidth}
      height={imageHeight}
    />
  );
}

export function makePicture(canvasRef, imageData, scale) {
  if (!canvasRef.current) return;
  const grayscaleData = imageData;
  const canvas = canvasRef.current;
  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.scale(scale, scale);

  for (let i = 0; i < 28; i++) {
    for (let j = 0; j < 28; j++) {
      const value = grayscaleData[i * 28 + j];
      ctx.fillStyle = `rgb(${value}, ${value}, ${value})`;
      ctx.fillRect(j, i, 1, 1);
    }
  }
  ctx.scale(1 / scale, 1 / scale);
}
