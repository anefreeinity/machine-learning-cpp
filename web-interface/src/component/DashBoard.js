import CanvasImage from "./CanvasImage";

export default function DashBoard({ width, height, selectedImage }) {
  return (
    <div
      style={{
        width: (width * 3) / 5,
        margin: 0,
        position: "absolute",
        top: `${height / 2}px`,
        left: `${width / 2 - (width * 3) / 10}px`,
      }}
      className="border border-zinc-600 z-10 bg-transparent text-white rounded"
    >
      <CustomCard selectedImage={selectedImage} />
    </div>
  );
}

function CustomCard({ selectedImage }) {
  let prediction = null;
  return (
    <div className="flex p-4">
      <div className="w-1/2">
        <p>Label for the image: {selectedImage.label}</p>
        <p className="pt-2">Predicted digit: {prediction}</p>
        <button className="absolute bottom-4 left-4 bg-transparent text-white font-semibold hover:text-white py-2 px-4 border border-zinc-600 hover:border-zinc-400 rounded">
          Predict
        </button>
      </div>
      <div className="w-1/2 flex justify-end">
        <CanvasImage
          className="rounded border border-zinc-800"
          imageWidth={200}
          imageHeight={200}
          imageData={selectedImage.image}
        />
      </div>
    </div>
  );
}
