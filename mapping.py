
DAY_MAP = {
    1: "Monday",
    2: "Tuesday",
    3: "Wednesday",
    4: "Thursday",
    5: "Friday",
    6: "Saturday",
    7: "Sunday"
    }


def map_hour_to_period(hour):
    if 5 <= hour <= 9:
        return "Morning (5-9)"
    elif 10 <= hour <= 13:
        return "Midday (10-13)"
    elif 14 <= hour <= 18:
        return "Afternoon (14-18)"
    elif 19 <= hour <= 23:
        return "Evening (19-23)"
    elif 0 <= hour <= 4:
        return "Night (0-4)"
    else:
        return None


injury_map = {
    "bez zraněn": "none",
    "lehké zranění": "minor",
    "těžké zranění": "severe",
    "usmrcení": "fatal"
}