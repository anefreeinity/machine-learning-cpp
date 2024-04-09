import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Autocomplete from "@mui/material/Autocomplete";
import CanvasImage from "./CanvasImage";

const romanNumerals = [
  { value: 1000, numeral: "M" },
  { value: 900, numeral: "CM" },
  { value: 500, numeral: "D" },
  { value: 400, numeral: "CD" },
  { value: 100, numeral: "C" },
  { value: 90, numeral: "XC" },
  { value: 50, numeral: "L" },
  { value: 40, numeral: "XL" },
  { value: 10, numeral: "X" },
  { value: 9, numeral: "IX" },
  { value: 5, numeral: "V" },
  { value: 4, numeral: "IV" },
  { value: 1, numeral: "I" },
];

function AutoComplete({
  width,
  height,
  images,
  className,
  setCurrentSelectedImage,
}) {
  return (
    <Autocomplete
      style={{
        margin: 0,
        position: "absolute",
        top: `${height / 4}px`,
        left: `${width / 2 - (width * 3) / 10 - 18}px`,
      }}
      onChange={(event, newImage) => {
        setCurrentSelectedImage(newImage);
        console.log(newImage);
      }}
      id="country-select-demo"
      sx={{ width: (width * 3) / 5 }}
      options={images}
      autoHighlight
      getOptionLabel={(option) => option.id}
      renderOption={(props, image) => (
        <Box
          component="li"
          sx={{ "& > img": { mr: 2, flexShrink: 0 } }}
          {...props}
          className="flex mb-4"
        >
          <div className="w-1/2">{image.id}</div>
          <div className="flex w-1/2 justify-end px-2">
            <CanvasImage
              imageWidth={25}
              imageHeight={25}
              imageData={image.image}
            />
          </div>
        </Box>
      )}
      renderInput={(params) => (
        <TextField
          {...params}
          label="Choose a digit"
          inputProps={{
            ...params.inputProps,
            autoComplete: "new-password",
          }}
        />
      )}
    />
  );
}

export function toRoman(num) {
  if (isNaN(num)) {
    return "";
  }
  let romanNumeral = "";
  for (let i = 0; i < romanNumerals.length; i++) {
    while (num >= romanNumerals[i].value) {
      romanNumeral += romanNumerals[i].numeral;
      num -= romanNumerals[i].value;
    }
  }
  return romanNumeral;
}

export default AutoComplete;
