import matplotlib.pyplot as plt
from election_results import results

year = input("Enter year: ")
state = input("Enter state: ")

if year not in results or state not in results[year]:
    print(f"No results found for {state} {year}")
else:
    state_data = results[year][state]

    dem_wasted_votes = []
    rep_wasted_votes = []
    for election in state_data:
        total_votes = election.dem_votes + election.rep_votes
        half_votes = total_votes / 2
        dem_wasted = max(0, election.dem_votes - half_votes)
        rep_wasted = max(0, election.rep_votes - half_votes)
        dem_wasted_votes.append(dem_wasted)
        rep_wasted_votes.append(rep_wasted)
#YOU CAN ONLY ENTER THE STATE IN ALL CAPS
    width = 0.51970
    plt.bar([i - width/2 for i in range(len(state_data))], dem_wasted_votes, width=width, label="Democratic Wasted Votes", color="#008cff")
    plt.bar([i + width/2 for i in range(len(state_data))], rep_wasted_votes, width=width, label="Republican Wasted Votes", color="#ff1605")
    plt.xticks(range(len(state_data)), [election.district for election in state_data])
    plt.xlabel("District")
    plt.ylabel("Wasted Votes")
    plt.title(f"Wasted Votes for Democrats and Republicans in {state} {year}")
    plt.legend()
    plt.savefig(f"{state}_{year}.png")
    plt.show()