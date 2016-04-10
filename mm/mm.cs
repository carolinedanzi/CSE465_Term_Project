// Caroline Danzi
// Dr. Zmuda
// CSE 465
// Mail Merge program - takes in a tab-separated file and a template
// file and returns individual files named wtih ID field with attributes
// plugged into <<tags>>
// Note: I looked at the Microsoft C# documentation for help with regex,
// Dictionaries, and some string methods.  I also looked at our class notes
// for the file io syntax.  Kyle B. also helped me with the regex.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.IO;

namespace CSE465 {

	public class MailMerge {
		
		private string tsvFile, tmpFile;
		private Dictionary<string, int> headers;
		
		public MailMerge(string tsvFile, string tmpFile) {
			this.tsvFile = tsvFile;
			this.tmpFile = tmpFile;
			this.headers = new Dictionary<string, int>();
		}
		
		public void parseTsv() {
			StreamReader tsvReader = new StreamReader(tsvFile);
			
			// The first line has the headers, so create
			// the dictionary of header and index pairs
			string headerLine = tsvReader.ReadLine();
			string[] tsvHeaders = headerLine.Split('\t');
			for(int i = 0; i < tsvHeaders.Length; i++) {
				headers.Add(tsvHeaders[i], i);
			}
			
			int idIndex = headers["ID"];
			StreamWriter output;
			StreamReader tmpReader;
			
			// Go through each line in the tsvFile
			while(!tsvReader.EndOfStream) {
				// Get the line, split it based on tab
				string line = tsvReader.ReadLine();
				string[] tokens = line.Split('\t');
				
				// Create and open the file for writing, and open
				// the template file for reading
				string fileName = tokens[idIndex] + ".txt";
				output = new StreamWriter(fileName);
				tmpReader = new StreamReader(tmpFile);
				
				// Go through each line in the template file and replace the
				// <<tags>> with the appropriate attribute from the tsv file
				while(!tmpReader.EndOfStream) {
					string templateLine = tmpReader.ReadLine();
					line = replaceHeaders(templateLine, tokens);
					output.WriteLine(line);
				}
						
				output.Close();
				tmpReader.Close();
			}
			
			tsvReader.Close();
			
		}
		
		// Takes in a line with <<tags>> and a string array of attributes
		// and replaces the <<tags>> with the appropriate attributes.
		private string replaceHeaders(string line, string[] tokens) {
			// Looked at https://msdn.microsoft.com/en-us/library/system.text.regularexpressions.regex(v=vs.110).aspx
			// for help with regular expressions in C#.  Also worked with Kyle B. 
			string pattern = @"<<(\w*)>>";
			Regex rx = new Regex(pattern, RegexOptions.IgnoreCase);
			MatchCollection matches = rx.Matches(line);
			
			foreach(Match m in matches) {
				// find the correct attribute based on the index of the header
				// stored in the headers dictionary 
				string attribute = tokens[headers[m.Groups[1].ToString()]];
				line = line.Replace(m.Value, attribute);
			}
			return line;
		}
		
		public static void Main(string[] args) {
			MailMerge mm = new MailMerge(args[0], args[1]);
			mm.parseTsv();
		}
	}

}