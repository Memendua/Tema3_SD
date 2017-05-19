#ifndef __IMDB__H__
#define __IMDB__H__

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

#include "movie.h"
#include "actor.h"
#include "director.h"
//#include "categories.h"

#define NONE                            "none"

#define ADD_MOVIE                       "add_movie"
#define ADD_USER                        "add_user"
#define ADD_ACTOR                       "add_actor"
#define ADD_RATING                      "add_rating"
#define UPDATE_RATING                   "update_rating"
#define REMOVE_RATING                   "remove_rating"
// queries
#define GET_RATING                      "get_rating"
#define GET_LONGEST_CAREER_ACTOR        "get_longest_career_actor"
#define GET_MOST_INFLUENTIAL_DIRECTOR   "get_most_influential_director"
#define GET_BEST_YEAR_FOR_CATEGORY      "get_best_year_for_category"
#define GET_2ND_DEGREE_COLLEAGUES       "get_2nd_degree_colleagues"
#define GET_TOP_K_MOST_RECENT_MOVIES    "get_top_k_most_recent_movies"
#define GET_TOP_K_ACTOR_PAIRS           "get_top_k_actor_pairs"
#define GET_TOP_K_PARTNERS_FOR_ACTOR    "get_top_k_partners_for_actor"
#define GET_TOP_K_MOST_POPULAR_MOVIES   "get_top_k_most_popular_movies"
#define GET_AVG_RATING_IN_RANGE         "get_avg_rating_in_range"


struct comp_by_ratings {
    bool operator() (const movie &movie1, const movie &movie2) const {
        if (movie1.nr_ratings() < movie2.nr_ratings()) {
            return true;
        } else if (movie1.nr_ratings() == movie2.nr_ratings()) {
            if (movie1.get_movie_id() > movie2.get_movie_id()) {
                return true;
            }
        }

        return false;
    }
};

class IMDb {
public:
    IMDb();
    ~IMDb();

    void add_movie(std::string movie_name, std::string movie_id, int timestamp,
                   std::vector<std::string> categories,
                   std::string director_name,
                   std::vector<std::string> actor_ids);

    void add_user(std::string user_id, std::string name);
    void add_actor(std::string actor_id, std::string name);

    void add_rating(std::string user_id, std::string movie_id, int rating);
    void update_rating(std::string user_id, std::string movie_id, int rating);
    void remove_rating(std::string user_id, std::string movie_id);

    // queries
    std::string get_rating(std::string movie_id);
    std::string get_longest_career_actor();
    std::string get_most_influential_director();
    std::string get_best_year_for_category(std::string category);
    std::string get_2nd_degree_colleagues(std::string actor_id);
    std::string get_top_k_most_recent_movies(int k);
    std::string get_top_k_actor_pairs(int k);
    std::string get_top_k_partners_for_actor(int k, std::string actor_id);
    std::string get_top_k_most_popular_movies(int k);
    std::string get_avg_rating_in_range(int start, int end);

    // input reader helper.
    std::string read_input_line(const std::string& line);

private:
    // Cheie: movie_id; Valoare: variabila de tip movie;
    std::unordered_map<std::string, movie> movies;
    // Filme sortate dupa an;
    std::map<int, movie&> recent_movies;
    std::map<int, movie&> rated_movies;
    std::set<movie, comp_by_ratings> popular_movies;
    // Cheie: actor_id; Valoare: variabila de tip actor;
    std::unordered_map<std::string, actor> actors;
    actor max_years;
    // Cheie: nume director; Valoare: variabila de tip director;
    std::unordered_map<std::string, director> directors;
    director max_coll;
    // Cheie: user_id; Valoare: user_name;
    std::unordered_map<std::string, std::string> users;
    // Cache pentru get_average_rating_in_range
    std::unordered_map<int, std::unordered_map<int, std::string> > cache;
};

#endif
