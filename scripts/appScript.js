const SHEET_ID = "15iTVJmxcmp_iSjnWljLElRV82z_YiZAwUv3tdZKtC7Y";

function doGet(e) {
  try {
    const ss = SpreadsheetApp.openById(SHEET_ID);
    const today = new Date();

    // Format date as "MMM-DD" (e.g., "Feb-02")
    const options = { month: "short", day: "2-digit" };
    const sheetName = today
      .toLocaleDateString("en-US", options)
      .replace(" ", "-");

    let sheet = ss.getSheetByName(sheetName);

    if (!sheet) {
      sheet = ss.insertSheet(sheetName);
      sheet.appendRow([
        "Timestamp",
        "Temperature (°C)",
        "Humidity (%)",
        "Rainfall (mm)",
        "Pressure",
        "Pressure Unit",
      ]);
    }

    const timestamp = today;
    const temp = e.parameter.temp;
    const humid = e.parameter.humid;
    const p = e.parameter.p;
    const rain = e.parameter.rain;
    const pUnit = e.parameter.pUnit;

    sheet.appendRow([timestamp, temp, humid, rain, p, pUnit]);

    return ContentService.createTextOutput("Success").setMimeType(
      ContentService.MimeType.TEXT
    );
  } catch (error) {
    Logger.log("Error: " + error.message);
    return ContentService.createTextOutput(
      "Error: " + error.message
    ).setMimeType(ContentService.MimeType.TEXT);
  }
}
