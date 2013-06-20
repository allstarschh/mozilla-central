[NoInterfaceObject]
interface RandomSource {
//  ArrayBufferView getRandomValues(ArrayBufferView array);
};

interface Crypto {
  readonly attribute SubtleCrypto subtle;
};

Crypto implements RandomSource;

interface SubtleCrypto {

};

//partial interface Window {
//  readonly attribute Crypto crypto;
//};
