using System.Security.Cryptography;
using System.Text;
namespace App{

	class Program{
		public static readonly HashAlgorithmName hashAlgorithm = HashAlgorithmName.SHA256;
	 	static void Main(){
			Console.Write("Insert your password to encrypt: ");
			string passwd = Console.ReadLine() ?? "";
			// string encryptedPassword = Encrypt(passwd);
			// Console.WriteLine("\n your password is: " + encryptedPassword);
			string cypheredPassword = Cypher(passwd);
			Console.WriteLine(cypheredPassword);

		}
	
		static string Encrypt(string input){

			Byte[] passwdInBytes = Encoding.UTF8.GetBytes(input); 
			Byte[] passwdHashInBytes = SHA256.HashData(passwdInBytes);

			string passwdHash = Convert.ToHexString(passwdHashInBytes);

			return passwdHash;
		}
		static string Cypher(string input){
			if (input == "") return "Error, no password has been entered";
			
			byte[] salt = new byte[8];
			
			using (RandomNumberGenerator rng = RandomNumberGenerator.Create()){
				rng.GetBytes(salt);
			}

			int maxIterations = 1000;
			try {
				byte[] k1 = Rfc2898DeriveBytes.Pbkdf2(
						Encoding.UTF8.GetBytes(input),
						salt,
						maxIterations,
						hashAlgorithm,
						16
						);
				Aes encryptionAlgorithm = Aes.Create();

				MemoryStream encryptionStream = new MemoryStream();

				encryptionStream.Write(encryptionAlgorithm.IV, 0, encryptionAlgorithm.IV.Length);

				CryptoStream encrypt = new CryptoStream(
					encryptionStream,
					encryptionAlgorithm.CreateEncryptor(),
					CryptoStreamMode.Write
				);

				byte[] utfD1 = Encoding.UTF8.GetBytes(input);
				encrypt.Write(utfD1, 0, utfD1.Length);
				encrypt.FlushFinalBlock();
				
			}
			catch{
				
			}

			return "";
		}
	}
}
