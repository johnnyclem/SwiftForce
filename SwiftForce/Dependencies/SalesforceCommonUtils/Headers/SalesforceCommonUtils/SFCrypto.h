//
//  CHCrypto.h
//  FileSDK
//
//  Created by Amol Prabhu on 1/11/12.
//  Copyright (c) 2012 Salesforce.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>

/**
 This class is responsible for encrypting and decrypting the content data for chatter.
 */

typedef enum {
    SFCryptoModeInMemory,
    SFCryptoModeDisk
    
} SFCryptoMode;


@interface SFCrypto : NSObject

/**
 The file to write the encrypted/decrypted data to used in CHCryptoModeDisk mode
 */
@property(nonatomic, copy) NSString *file;

/**
 Returns the current mode of operation of the CHCrypto class
 */
@property (nonatomic, readonly) SFCryptoMode mode;

/**
 Designated initializer
 @param operation operation to be performed encrypt/decrypt
 @param key Key used for encyption/decryption pass nil to use the default key
 @param mode Mode which determines whether to perform operation in memory at once or in chunks writing to the disk
 */
- (id)initWithOperation:(CCOperation)operation key:(NSData *)key mode:(SFCryptoMode)mode;

/**
 Encrypts or decrypts the passed in data, the input data is assumed to be passed in as a chunk
 Method requires finalizeCipher to be called
 @param data input data
 */
- (void)cryptData:(NSData *)inData;

/**
 Decrypt the passed in data initializer, performs the decryption in memory
 @param data encrypted input data
 */
- (NSData *)decryptDataInMemory:(NSData *)data;

/**
 Encrypt the passed in data initializer, performs the encryption in memory
 @param data input data
 */
- (NSData *)encryptDataInMemory:(NSData *)data;

/**
 Finalize the the encryption/decryption process
 */
- (BOOL)finalizeCipher;

/**
 Decrypts a file.
 @param inputFile the name of the encrypted file
 @param outputFile the name of the decrypted file
 @result YES if the file was successfully decrypted; NO otherwise
 */
-(BOOL) decrypt:(NSString *)inputFile to:(NSString *)outputFile;

/**
 Creates a secret key, based in part on the input key.
 @param key The base key which will seed the return key.
 @result The secret key, based on the input key.
 */
+ (NSData *)secretWithKey:(NSString *)key;

/**
 Returns a unique identifier associated with this app install.  The identifier will
 remain the same for the lifetime of the app's installation on the device.  If the
 app is uninstalled, a new identifier will be created if it is ever reinstalled.
 @result A unique identifier for the app install on the particular device.
 */
+ (NSString *)baseAppIdentifier;

/**
 Returns whether we have an initialization vector used for encryption stored in the keychain.
 */
+ (BOOL)hasInitializationVector;

/** The default secret used by chatter for encryption and decryption.
 */
+ (NSData *)chatterCryptoSecret;

@end