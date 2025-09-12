import pandas
import click

PATH = "dopravni_nehody_-1895066464895987623.csv"

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


DATA_FRAME = pandas.read_csv(PATH, sep=",", low_memory=False).drop_duplicates(subset="id_nehody")


#calculates percentage of all accidents caused by alcohol
#not all accidents have found the cause - option "nezjistovano"
def caused_by_alcohol(DATA_FRAME):
    alcohol_caused_accidents = (
        (DATA_FRAME["alkohol_vinik"] == "ano")
        .mean()
        .mul(100)
        .round(2)
    )
    return alcohol_caused_accidents
    

#calculates percentage of all accidents per day of the week
#sorted by the highest percentage first
def percent_per_day(DATA_FRAME):
    day_percentages = (
        DATA_FRAME["den"]
        .replace(DAY_MAP)
        .value_counts(normalize=True)
        .mul(100)
        .round(2)
        .to_dict()
    )
    return day_percentages


#calculates percentage of all accidents per time of day
def percent_per_day_time(DATA_FRAME):
    periods = DATA_FRAME["hodina"].apply(map_hour_to_period).dropna()
    time_of_day = (
        periods.value_counts(normalize=True)
        .mul(100)
        .round(2)
        .to_dict()
    )
    return time_of_day


#calculates relation between injuries and people without a seatbelt
def seatbelt_injury(DATA_FRAME):
    pass


#calculates the most dangerous city parts
def city_part(DATA_FRAME):
    pass




# ---------- CLI ----------
@click.group()
def cli():
    pass

@cli.command()
def alcohol():
    print("Percentage of accidents directly caused by alcohol")
    print(caused_by_alcohol(DATA_FRAME))

@cli.command()
def days():
    print("Days sorted by the most accidents")
    for day, value in percent_per_day(DATA_FRAME).items():
        print(f"{day}: {value}%")

@cli.command()
def time():
    print("Times of day with the most accidents")
    for time, value in percent_per_day_time(DATA_FRAME).items():
        print(f"{time}: {value}%")




if __name__ == "__main__":
    cli()