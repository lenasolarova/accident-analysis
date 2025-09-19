import pandas
import click

import mapping

#TODO delete after I am done with changing mapping.py
import importlib
importlib.reload(mapping)

PATH = "../dopravni_nehody_-1895066464895987623.csv"

"""
dataframe with no duplicates = duplicate in this file means 
the same accident_id (id_nehody) because every person 
involved is logged separately under the same id
"""

DATA_FRAME_NON_DUP = pandas.read_csv(
    PATH, sep=",", 
    low_memory=False).drop_duplicates(subset="id_nehody")

"""no duplicate dataframe"""
DATA_FRAME_ALL = pandas.read_csv(
    PATH, sep=",", 
    low_memory=False)

#calculates percentage of all accidents caused by alcohol
#not all accidents have found the cause - option "nezjistovano"
def caused_by_alcohol(DATA_FRAME_NON_DUP):
    mask = DATA_FRAME_NON_DUP["alkohol_vinik"] != "nezjistovano"
    alcohol_caused_accidents = (
        (DATA_FRAME_NON_DUP.loc[mask, "alkohol_vinik"] == "ano")
        .mean() * 100)

    return round(alcohol_caused_accidents, 2)
    

#calculates percentage of all accidents per day of the week
def percent_per_day(DATA_FRAME_NON_DUP):
    day_series = DATA_FRAME_NON_DUP["den"].replace(mapping.DAY_MAP)

    day_percentages = (
        day_series
        .value_counts(normalize=True)
        .mul(100)
        .round(2)
    )

    ordered_days = [mapping.DAY_MAP[i] for i in sorted(mapping.DAY_MAP.keys())]
    day_percentages = day_percentages.reindex(ordered_days, fill_value=0)

    return day_percentages.to_dict()

#calculates relation between injuries and drivers 
#without a seatbelt and under the influence
def seatbelt_injury(DATA_FRAME_ALL):
    df = (
        DATA_FRAME_ALL
        .dropna(subset=[
            "stav_ridic",
            "nasledek",
            "ozn_osoba",
            "osoba"
        ])
        .query("osoba.str.contains('řidič')", engine="python")
        .assign(
            dui=lambda d: d["stav_ridic"].str.contains(
                r"Pod vlivem alkoholu|Pod vlivem drog|Pod vlivem léků", case=False, na=False
            ),
            no_seatbelt=lambda d: d["ozn_osoba"].str.contains(
                r"bezpečnostní vak \(airbag\) v činnosti - osoba nepřipoutaná|nepřipoutaný bezpečnostními pásy",
                case=False, na=False
            ),
            injury=lambda d: d["nasledek"].map(mapping.injury_map),
        )
    )

    order = ["none", "minor", "severe", "fatal"]
    summary = pandas.crosstab(
        [df["dui"], df["no_seatbelt"]],
        df["injury"],
        normalize="index"
    ).reindex(columns=order).mul(100).round(2)

    return summary


# ------------------------------ CLI ------------------------------
@click.group(help="This script analyzes car accidents from Brno, Czechia")
def cli():
    pass

@cli.command(help="Percentage of accidents directly caused by alcohol")
def alcohol():
    print("Percentage of accidents directly caused by alcohol")
    print(caused_by_alcohol(DATA_FRAME_NON_DUP))

@cli.command(help="Days of the week by their respective percentage of accidents:")
def days():
    print("Days of the week by their respective percentage of accidents:")
    for day, value in percent_per_day(DATA_FRAME_NON_DUP).items():
        print(f"{day}: {value}%")

@cli.command(help="Relationship between driver driving under the influence," \
    "wearing a seatbelt and resulting injury")
def seatbelt():
    print("Relationship between driver driving under the influence," \
    "wearing a seatbelt and resulting injury")
    print(seatbelt_injury(DATA_FRAME_ALL))


if __name__ == "__main__":
    cli()