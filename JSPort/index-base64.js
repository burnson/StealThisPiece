function decodeBase64ToArrayBuffer(input) {
  function encodedValue(input, index) {
    var encodedCharacter;
    if (index < input.length) {
      var x = input.charCodeAt(index);
      if (x >= 65 && x <= 90) {
        encodedCharacter = x - 65;
      } else if (x >= 97 && x <= 122) {
        encodedCharacter = x - 71;
      } else if (x >= 48 && x <= 57) {
        encodedCharacter = x + 4;
      } else if (x === 43) {
        encodedCharacter = 62;
      } else if (x === 47) {
        encodedCharacter = 63;
      } else if (x !== 61) {
        console.log('base64 encountered unexpected character code: ' + x);
      }
    }
    return encodedCharacter;
  }
  
  if (input.length === 0 || (input.length % 4) > 0) {
    console.log('base64 encountered unexpected length: ' + input.length);
    return;
  }
  
  var padding = (input.charAt(input.length - 1) === '=' ? 1 : 0) +
                (input.charAt(input.length - 2) === '=' ? 1 : 0);
  var decodedLength = input.length * 3 / 4 - padding;
  var buffer = new ArrayBuffer(decodedLength);
  var bufferView = new Uint8Array(buffer);
  var encoded1, encoded2, encoded3, encoded4;
  var d = 0, e = 0;
  while (d < decodedLength) {
    encoded1 = encodedValue(input, e++);
    encoded2 = encodedValue(input, e++);
    encoded3 = encodedValue(input, e++);
    encoded4 = encodedValue(input, e++);
    bufferView[d++] = (encoded1 << 2) | (encoded2 >> 4);
    if (d < decodedLength) {
      bufferView[d++] = ((encoded2 & 15) << 4) | (encoded3 >> 2);
    }
    if (d < decodedLength) {
      bufferView[d++] = ((encoded3 &  3) << 6) |  encoded4;
    }
  }
  return buffer;
}
