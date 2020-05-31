# reme Part 2

## Solution

Looking at the decompiled code, it seems as if there is another program "inside the program" with the function `Check`:
```cs
byte[] iLAsByteArray = typeof(Program).GetMethod("InitialCheck", BindingFlags.Static | BindingFlags.NonPublic)!.GetMethodBody()!.GetILAsByteArray();
byte[] array = File.ReadAllBytes(Assembly.GetExecutingAssembly().Location);
int[] array2 = array.Locate(Encoding.ASCII.GetBytes("THIS_IS_CSCG_NOT_A_MALWARE!"));
MemoryStream memoryStream = new MemoryStream(array);
memoryStream.Seek(array2[0] + Encoding.ASCII.GetBytes("THIS_IS_CSCG_NOT_A_MALWARE!").Length, SeekOrigin.Begin);
byte[] array3 = new byte[memoryStream.Length - memoryStream.Position];
memoryStream.Read(array3, 0, array3.Length);
byte[] rawAssembly = AES_Decrypt(array3, iLAsByteArray);
object obj = Assembly.Load(rawAssembly).GetTypes()[0].GetMethod("Check", BindingFlags.Static | BindingFlags.Public)!.Invoke(null, new object[1]
{
	args
});
```

The question is how we can modify the program without changing the assembly of the program itself. I found this blogpost about a similar
reversing challenge: https://bananamafia.dev/post/dotnet-re-cccamp19/

Following this we can create a new program with modified code which reads the assembly from the original program:
```cs
...
byte[] array = File.ReadAllBytes("ReMe.dll");
byte[] iLAsByteArray = Assembly.Load(array).GetTypes()[1].GetMethod("InitialCheck", BindingFlags.Static | BindingFlags.NonPublic).GetMethodBody().GetILAsByteArray();
...
```

Which then results in something like this (which dumps the new program to `new.dll`):
```cs
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Collections.Generic;
using System.Linq;

internal class Program
{
	static Program()
	{
		Initialize();
	}

	private static void Main(string[] args)
	{
		InitialCheck(args);
		byte[] array = File.ReadAllBytes("ReMe.dll");
		byte[] iLAsByteArray = Assembly.Load(array).GetTypes()[1].GetMethod("InitialCheck", BindingFlags.Static | BindingFlags.NonPublic).GetMethodBody().GetILAsByteArray();
		int[] array2 = ByteArrayRocks.Locate(array, Encoding.ASCII.GetBytes("THIS_IS_CSCG_NOT_A_MALWARE!"));
		MemoryStream memoryStream = new MemoryStream(array);
		memoryStream.Seek(array2[0] + Encoding.ASCII.GetBytes("THIS_IS_CSCG_NOT_A_MALWARE!").Length, SeekOrigin.Begin);
		byte[] array3 = new byte[memoryStream.Length - memoryStream.Position];
		memoryStream.Read(array3, 0, array3.Length);
		byte[] rawAssembly = AES_Decrypt(array3, iLAsByteArray);
		object obj = Assembly.Load(rawAssembly).GetTypes()[0].GetMethod("Check", BindingFlags.Static | BindingFlags.Public).Invoke(null, new object[1]
		{
			args
		});
		Console.WriteLine(rawAssembly);
		File.WriteAllBytes("new.dll", rawAssembly);
	}

	public static string CalculateMD5Hash(byte[] input)
	{
		MD5 mD = MD5.Create();
		byte[] array = mD.ComputeHash(input);
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < array.Length; i++)
		{
			stringBuilder.Append(array[i].ToString("X2"));
		}
		return stringBuilder.ToString();
	}

	[DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true)]
	private static extern bool CheckRemoteDebuggerPresent(IntPtr hProcess, ref bool isDebuggerPresent);

	[DllImport("kernel32.dll")]
	private static extern bool IsDebuggerPresent();

	[DllImport("kernel32.dll", CharSet = CharSet.Auto)]
	public static extern IntPtr GetModuleHandle(string lpModuleName);

	[DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
	private static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

	private static void InitialCheck(string[] args)
	{
		Initialize();
		if (Debugger.IsAttached)
		{
			Console.WriteLine("Nope");
			Environment.Exit(-1);
		}
		bool isDebuggerPresent = true;
		CheckRemoteDebuggerPresent(Process.GetCurrentProcess().Handle, ref isDebuggerPresent);
		if (isDebuggerPresent)
		{
			Console.WriteLine("Nope");
			Environment.Exit(-1);
		}
		if (IsDebuggerPresent())
		{
			Console.WriteLine("Nope");
			Environment.Exit(-1);
		}
		if (args.Length == 0)
		{
			Console.WriteLine("Usage: ReMe.exe [password] [flag]");
			Environment.Exit(-1);
		}
		if (args[0] != StringEncryption.Decrypt("D/T9XRgUcKDjgXEldEzeEsVjIcqUTl7047pPaw7DZ9I="))
		{
			Console.WriteLine("Nope");
			Environment.Exit(-1);
		}
		else
		{
			Console.WriteLine("There you go. Thats the first of the two flags! CSCG{{{0}}}", args[0]);
		}
		IntPtr moduleHandle = GetModuleHandle("kernel32.dll");
		if (moduleHandle != IntPtr.Zero)
		{
			IntPtr procAddress = GetProcAddress(moduleHandle, "CheckRemoteDebuggerPresent");
			if (Marshal.ReadByte(procAddress) == 233)
			{
				Console.WriteLine("Nope!");
				Environment.Exit(-1);
			}
		}
	}

	public static byte[] AES_Encrypt(byte[] bytesToBeEncrypted, byte[] passwordBytes)
	{
		byte[] result = null;
		byte[] salt = new byte[8]
		{
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8
		};
		using (MemoryStream memoryStream = new MemoryStream())
		{
			using (RijndaelManaged rijndaelManaged = new RijndaelManaged())
			{
				rijndaelManaged.KeySize = 256;
				rijndaelManaged.BlockSize = 128;
				Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(passwordBytes, salt, 1000);
				rijndaelManaged.Key = rfc2898DeriveBytes.GetBytes(rijndaelManaged.KeySize / 8);
				rijndaelManaged.IV = rfc2898DeriveBytes.GetBytes(rijndaelManaged.BlockSize / 8);
				rijndaelManaged.Mode = CipherMode.CBC;
				using (CryptoStream cryptoStream = new CryptoStream(memoryStream, rijndaelManaged.CreateEncryptor(), CryptoStreamMode.Write))
				{
					cryptoStream.Write(bytesToBeEncrypted, 0, bytesToBeEncrypted.Length);
					cryptoStream.Close();
				}
				result = memoryStream.ToArray();
			}
		}
		return result;
	}

	public static byte[] AES_Decrypt(byte[] bytesToBeDecrypted, byte[] passwordBytes)
	{
		byte[] result = null;
		byte[] salt = new byte[8]
		{
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8
		};
		using (MemoryStream memoryStream = new MemoryStream())
		{
			using (RijndaelManaged rijndaelManaged = new RijndaelManaged())
			{
				rijndaelManaged.KeySize = 256;
				rijndaelManaged.BlockSize = 128;
				Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(passwordBytes, salt, 1000);
				rijndaelManaged.Key = rfc2898DeriveBytes.GetBytes(rijndaelManaged.KeySize / 8);
				rijndaelManaged.IV = rfc2898DeriveBytes.GetBytes(rijndaelManaged.BlockSize / 8);
				rijndaelManaged.Mode = CipherMode.CBC;
				using (CryptoStream cryptoStream = new CryptoStream(memoryStream, rijndaelManaged.CreateDecryptor(), CryptoStreamMode.Write))
				{
					cryptoStream.Write(bytesToBeDecrypted, 0, bytesToBeDecrypted.Length);
					cryptoStream.Close();
				}
				result = memoryStream.ToArray();
			}
		}
		return result;
	}

	[DllImport("kernel32.dll")]
	private unsafe static extern bool VirtualProtect(byte* lpAddress, int dwSize, uint flNewProtect, out uint lpflOldProtect);

	private unsafe static void Initialize()
	{
		Module module = typeof(Program).Module;
		byte* ptr = (byte*)(void*)Marshal.GetHINSTANCE(module);
		byte* ptr2 = ptr + 60;
		byte* ptr3;
		ptr2 = (ptr3 = ptr + *(uint*)ptr2);
		ptr2 += 6;
		ushort num = *(ushort*)ptr2;
		ptr2 += 14;
		ushort num2 = *(ushort*)ptr2;
		ptr2 = (ptr3 = ptr2 + 4 + (int)num2);
		byte* ptr4 = stackalloc byte[11];
		uint lpflOldProtect;
		if (module.FullyQualifiedName[0] != '<')
		{
			byte* ptr5 = ptr + *(uint*)(ptr2 - 16);
			if (*(uint*)(ptr2 - 120) != 0)
			{
				byte* ptr6 = ptr + *(uint*)(ptr2 - 120);
				byte* ptr7 = ptr + *(uint*)ptr6;
				byte* ptr8 = ptr + *(uint*)(ptr6 + 12);
				byte* ptr9 = ptr + *(uint*)ptr7 + 2;
				VirtualProtect(ptr8, 11, 64u, out lpflOldProtect);
				*(int*)ptr4 = 1818522734;
				*(int*)(ptr4 + 4) = 1818504812;
				*(short*)(ptr4 + 4L * 2L) = 108;
				ptr4[10] = 0;
				for (int i = 0; i < 11; i++)
				{
					ptr8[i] = ptr4[i];
				}
				VirtualProtect(ptr9, 11, 64u, out lpflOldProtect);
				*(int*)ptr4 = 1866691662;
				*(int*)(ptr4 + 4) = 1852404846;
				*(short*)(ptr4 + 4L * 2L) = 25973;
				ptr4[10] = 0;
				for (int j = 0; j < 11; j++)
				{
					ptr9[j] = ptr4[j];
				}
			}
			for (int k = 0; k < num; k++)
			{
				VirtualProtect(ptr2, 8, 64u, out lpflOldProtect);
				Marshal.Copy(new byte[8], 0, (IntPtr)(void*)ptr2, 8);
				ptr2 += 40;
			}
			VirtualProtect(ptr5, 72, 64u, out lpflOldProtect);
			byte* ptr10 = ptr + *(uint*)(ptr5 + 8);
			*(int*)ptr5 = 0;
			*(int*)(ptr5 + 4) = 0;
			*(int*)(ptr5 + 2L * 4L) = 0;
			*(int*)(ptr5 + 3L * 4L) = 0;
			VirtualProtect(ptr10, 4, 64u, out lpflOldProtect);
			*(int*)ptr10 = 0;
			ptr10 += 12;
			uint num3 = *(uint*)ptr10;
			if (num3 > 40000)
			{
				return;
			}
			ptr10 += *(uint*)ptr10;
			ptr10 = (byte*)(((long)ptr10 + 7) & -4);
			ptr10 += 2;
			ushort num4 = *ptr10;
			ptr10 += 2;
			for (int l = 0; l < num4; l++)
			{
				VirtualProtect(ptr10, 8, 64u, out lpflOldProtect);
				ptr10 += 4;
				ptr10 += 4;
				for (int m = 0; m < 8; m++)
				{
					VirtualProtect(ptr10, 4, 64u, out lpflOldProtect);
					*ptr10 = 0;
					ptr10++;
					if (*ptr10 == 0)
					{
						ptr10 += 3;
						break;
					}
					*ptr10 = 0;
					ptr10++;
					if (*ptr10 == 0)
					{
						ptr10 += 2;
						break;
					}
					*ptr10 = 0;
					ptr10++;
					if (*ptr10 == 0)
					{
						ptr10++;
						break;
					}
					*ptr10 = 0;
					ptr10++;
				}
			}
			return;
		}
		uint num5 = *(uint*)(ptr2 - 16);
		uint num6 = *(uint*)(ptr2 - 120);
		uint[] array = new uint[num];
		uint[] array2 = new uint[num];
		uint[] array3 = new uint[num];
		for (int n = 0; n < num; n++)
		{
			VirtualProtect(ptr2, 8, 64u, out lpflOldProtect);
			Marshal.Copy(new byte[8], 0, (IntPtr)(void*)ptr2, 8);
			array[n] = *(uint*)(ptr2 + 12);
			array2[n] = *(uint*)(ptr2 + 8);
			array3[n] = *(uint*)(ptr2 + 20);
			ptr2 += 40;
		}
		if (num6 != 0)
		{
			for (int num7 = 0; num7 < num; num7++)
			{
				if (array[num7] <= num6 && num6 < array[num7] + array2[num7])
				{
					num6 = num6 - array[num7] + array3[num7];
					break;
				}
			}
			byte* ptr11 = ptr + num6;
			uint num8 = *(uint*)ptr11;
			for (int num9 = 0; num9 < num; num9++)
			{
				if (array[num9] <= num8 && num8 < array[num9] + array2[num9])
				{
					num8 = num8 - array[num9] + array3[num9];
					break;
				}
			}
			byte* ptr12 = ptr + num8;
			uint num10 = *(uint*)(ptr11 + 12);
			for (int num11 = 0; num11 < num; num11++)
			{
				if (array[num11] <= num10 && num10 < array[num11] + array2[num11])
				{
					num10 = num10 - array[num11] + array3[num11];
					break;
				}
			}
			uint num12 = *(uint*)ptr12 + 2;
			for (int num13 = 0; num13 < num; num13++)
			{
				if (array[num13] <= num12 && num12 < array[num13] + array2[num13])
				{
					num12 = num12 - array[num13] + array3[num13];
					break;
				}
			}
			VirtualProtect(ptr + num10, 11, 64u, out lpflOldProtect);
			*(int*)ptr4 = 1818522734;
			*(int*)(ptr4 + 4) = 1818504812;
			*(short*)(ptr4 + 4L * 2L) = 108;
			ptr4[10] = 0;
			for (int num14 = 0; num14 < 11; num14++)
			{
				(ptr + num10)[num14] = ptr4[num14];
			}
			VirtualProtect(ptr + num12, 11, 64u, out lpflOldProtect);
			*(int*)ptr4 = 1866691662;
			*(int*)(ptr4 + 4) = 1852404846;
			*(short*)(ptr4 + 4L * 2L) = 25973;
			ptr4[10] = 0;
			for (int num15 = 0; num15 < 11; num15++)
			{
				(ptr + num12)[num15] = ptr4[num15];
			}
		}
		for (int num16 = 0; num16 < num; num16++)
		{
			if (array[num16] <= num5 && num5 < array[num16] + array2[num16])
			{
				num5 = num5 - array[num16] + array3[num16];
				break;
			}
		}
		byte* ptr13 = ptr + num5;
		VirtualProtect(ptr13, 72, 64u, out lpflOldProtect);
		uint num17 = *(uint*)(ptr13 + 8);
		for (int num18 = 0; num18 < num; num18++)
		{
			if (array[num18] <= num17 && num17 < array[num18] + array2[num18])
			{
				num17 = num17 - array[num18] + array3[num18];
				break;
			}
		}
		*(int*)ptr13 = 0;
		*(int*)(ptr13 + 4) = 0;
		*(int*)(ptr13 + 2L * 4L) = 0;
		*(int*)(ptr13 + 3L * 4L) = 0;
		byte* ptr14 = ptr + num17;
		VirtualProtect(ptr14, 4, 64u, out lpflOldProtect);
		*(int*)ptr14 = 0;
		ptr14 += 12;
		ptr14 += *(uint*)ptr14;
		ptr14 = (byte*)(((long)ptr14 + 7) & -4);
		ptr14 += 2;
		ushort num19 = *ptr14;
		ptr14 += 2;
		for (int num20 = 0; num20 < num19; num20++)
		{
			VirtualProtect(ptr14, 8, 64u, out lpflOldProtect);
			ptr14 += 4;
			ptr14 += 4;
			for (int num21 = 0; num21 < 8; num21++)
			{
				VirtualProtect(ptr14, 4, 64u, out lpflOldProtect);
				*ptr14 = 0;
				ptr14++;
				if (*ptr14 == 0)
				{
					ptr14 += 3;
					break;
				}
				*ptr14 = 0;
				ptr14++;
				if (*ptr14 == 0)
				{
					ptr14 += 2;
					break;
				}
				*ptr14 = 0;
				ptr14++;
				if (*ptr14 == 0)
				{
					ptr14++;
					break;
				}
				*ptr14 = 0;
				ptr14++;
			}
		}
	}
}

internal static class ByteArrayRocks
{
	private static readonly int[] Empty = new int[0];

	public static int[] Locate(this byte[] self, byte[] candidate)
	{
		if (IsEmptyLocate(self, candidate))
		{
			return Empty;
		}
		List<int> list = new List<int>();
		for (int i = 0; i < self.Length; i++)
		{
			if (IsMatch(self, i, candidate))
			{
				list.Add(i);
			}
		}
		return (list.Count == 0) ? Empty : list.ToArray();
	}

	private static bool IsMatch(byte[] array, int position, byte[] candidate)
	{
		if (candidate.Length > array.Length - position)
		{
			return false;
		}
		for (int i = 0; i < candidate.Length; i++)
		{
			if (array[position + i] != candidate[i])
			{
				return false;
			}
		}
		return true;
	}

	private static bool IsEmptyLocate(byte[] array, byte[] candidate)
	{
		return array == null || candidate == null || array.Length == 0 || candidate.Length == 0 || candidate.Length > array.Length;
	}
}


public static class StringEncryption
{
	public static string Encrypt(string clearText)
	{
		string password = "A_Wise_Man_Once_Told_Me_Obfuscation_Is_Useless_Anyway";
		byte[] bytes = Encoding.Unicode.GetBytes(clearText);
		using (Aes aes = Aes.Create())
		{
			Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(password, new byte[13]
			{
				73,
				118,
				97,
				110,
				32,
				77,
				101,
				100,
				118,
				101,
				100,
				101,
				118
			});
			aes.Key = rfc2898DeriveBytes.GetBytes(32);
			aes.IV = rfc2898DeriveBytes.GetBytes(16);
			using (MemoryStream memoryStream = new MemoryStream())
			{
				using (CryptoStream cryptoStream = new CryptoStream(memoryStream, aes.CreateEncryptor(), CryptoStreamMode.Write))
				{
					cryptoStream.Write(bytes, 0, bytes.Length);
					cryptoStream.Close();
				}
				clearText = Convert.ToBase64String(memoryStream.ToArray());
			}
		}
		return clearText;
	}

	public static string Decrypt(string cipherText)
	{
		string password = "A_Wise_Man_Once_Told_Me_Obfuscation_Is_Useless_Anyway";
		cipherText = cipherText.Replace(" ", "+");
		byte[] array = Convert.FromBase64String(cipherText);
		using (Aes aes = Aes.Create())
		{
			Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(password, new byte[13]
			{
				73,
				118,
				97,
				110,
				32,
				77,
				101,
				100,
				118,
				101,
				100,
				101,
				118
			});
			aes.Key = rfc2898DeriveBytes.GetBytes(32);
			aes.IV = rfc2898DeriveBytes.GetBytes(16);
			using (MemoryStream memoryStream = new MemoryStream())
			{
				using (CryptoStream cryptoStream = new CryptoStream(memoryStream, aes.CreateDecryptor(), CryptoStreamMode.Write))
				{
					cryptoStream.Write(array, 0, array.Length);
					cryptoStream.Close();
				}
				cipherText = Encoding.Unicode.GetString(memoryStream.ToArray());
			}
		}
		return cipherText;
	}
}
```

Running `dotnet .\new.dll` doesn't do anything. Putting the file in ILSpy does reveal something though:
```cs
using System;
using System.Security.Cryptography;
using System.Text;

public class Inner
{
	public static void Check(string[] args)
	{
		if (args.Length <= 1)
		{
			Console.WriteLine("Nope.");
			return;
		}
		string[] array = args[1].Split(new string[1]
		{
			"_"
		}, StringSplitOptions.RemoveEmptyEntries);
		if (array.Length != 8)
		{
			Console.WriteLine("Nope.");
		}
		else if ("CSCG{" + array[0] == "CSCG{n0w" && array[1] == "u" && array[2] == "know" && array[3] == "st4t1c" && array[4] == "and" && CalculateMD5Hash(array[5]).ToLower() == "b72f3bd391ba731a35708bfd8cd8a68f" && array[6] == "dotNet" && array[7] + "}" == "R3333}")
		{
			Console.WriteLine("Good job :)");
		}
	}

	public static string CalculateMD5Hash(string input)
	{
		MD5 mD = MD5.Create();
		byte[] bytes = Encoding.ASCII.GetBytes(input);
		byte[] array = mD.ComputeHash(bytes);
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < array.Length; i++)
		{
			stringBuilder.Append(array[i].ToString("X2"));
		}
		return stringBuilder.ToString();
	}
}
```

We can then construct the flag from the following line:
```cs
else if ("CSCG{" + array[0] == "CSCG{n0w" && array[1] == "u" && array[2] == "know" && array[3] == "st4t1c" && array[4] == "and" && CalculateMD5Hash(array[5]).ToLower() == "b72f3bd391ba731a35708bfd8cd8a68f" && array[6] == "dotNet" && array[7] + "}" == "R3333}")
```

Flag: `CSCG{n0w_u_know_st4t1c_and_dynamic_dotNet_R3333}`


## Mitigation

The same as in the reme Part 1 write-up.
