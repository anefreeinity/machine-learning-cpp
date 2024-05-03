import CanvasImage from "./CanvasImage";

export default function DashBoard({
  width,
  height,
  selectedImage,
  prediction,
  setPrediction,
}) {
  let dashboardClass = "border-zinc-600";
  if (prediction && prediction === selectedImage.label) {
    dashboardClass = "border-green-900";
  } else if (prediction && prediction !== selectedImage.label) {
    dashboardClass = "border-red-900";
  }

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
      <CustomCard
        selectedImage={selectedImage}
        prediction={prediction}
        setPrediction={setPrediction}
      />
    </div>
  );
}

function CustomCard({ selectedImage, prediction, setPrediction }) {
  function handelPrediction() {
    predictDigit(selectedImage, setPrediction);
  }

  return (
    <div className="flex p-4">
      <div className="w-1/2">
        <p>Label for the image: {selectedImage.label}</p>
        {prediction && <p className="pt-2">Predicted digit: {prediction}</p>}
        <button
          onClick={handelPrediction}
          className="absolute bottom-4 left-4 bg-transparent text-white font-semibold hover:text-white py-2 px-4 border border-zinc-600 hover:border-zinc-400 rounded"
        >
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

async function predictDigit(selectedImage, setPrediction) {
  console.log("sending api request...");
  // console.log(JSON.stringify(selectedImage.image));
  // console.log(`length ${JSON.stringify(selectedImage.image).length}`);

  const URL = "http://127.0.0.1:5000/api/predict";
  const jsonData = JSON.stringify(selectedImage.image);
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
