// Copyright 2017 Popa Bogdan, Rosca Alin-Costin
#include <limits.h>
#include <iterator>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>

#include "include/imdb.h"


IMDb::IMDb() {
    // initialize what you need here.
    rated_movies_up_to_date = false;
    // checked_actor = false,
    // unchecked = true;
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp,  // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids) {
    // Adaugare film in baza de date;
    movie m(movie_name, movie_id, timestamp, categories, director_name,
            actor_ids);
    std::pair<std::string, movie> elem(movie_id, m);
    movies.insert(elem);
    recent_movies.emplace(timestamp, movies[movie_id]);

    // Se schimba topul de popularitate
    popular_movies.clear();


    // Caut directorul in baza de date
    auto found_director = directors.find(director_name);

    if (found_director == directors.end()) {
        std::pair<std::string, director> elem(director_name,
                                              director(director_name));
        found_director = directors.insert(elem).first;
    }

    for (unsigned int i = 0; i < actor_ids.size(); ++i) {
        // Se adauga sau se actualizeaza datele despre un actor;
        actor &current_actor = actors[actor_ids[i]];
        int &debut_year = current_actor.get_debut_year();
        int &last_year = current_actor.get_last_year();
        int &years = current_actor.get_years();

        // Se actualizeaza anul de debut;
        if (debut_year > timestamp) {
            debut_year = timestamp;
        }

        // Se actualizeaza ultimul an;
        if (last_year < timestamp) {
            last_year = timestamp;
        }

        // Se actualizeaza anii de activitate;
        years = last_year - debut_year;
        if (max_years < current_actor || max_years.get_id() == "") {
            max_years = current_actor;
        }

        // Se actualizeaza colaborarile regizorului;
        if (!found_director->second.check_collaboration(actor_ids[i])) {
            found_director->second.add_collaboration(actor_ids[i]);
        }

        // Se actualizeaza lista de colegi a fiecarui actor;
        // for (unsigned int j = 0; j < actor_ids.size(); ++j) {
        //     if (i == j) {
        //         continue;
        //     } else {
        //         if (checked_actor) {
        //             actors[actor_ids[j]].check();
        //         }
        //         actors[actor_ids[i]].add_colleague(actor_ids[j]);
        //     }
        // }
    }

    if (max_coll < found_director->second) {
        max_coll = found_director->second;
    }
}

void IMDb::add_user(std::string user_id, std::string name) {
    std::pair<std::string, std::string> user(user_id, name);
    users.insert(user);
}

void IMDb::add_actor(std::string actor_id, std::string name) {
    actor new_actor(actor_id, name);
    std::pair<std::string, actor> elem(actor_id, new_actor);
    actors.insert(elem);
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating) {
    // Rating-ul se modifica, trebuie modificat map-ul de recent_movies
    rated_movies_up_to_date = false;
    // Se schimba topul de popularitate
    popular_movies.clear();
    movie &current_movie = movies[movie_id];
    double old_rating = current_movie.add_rating(user_id, rating);
    if (current_movie.nr_ratings() == 1) {
        rated_movies.emplace(current_movie.get_timestamp(), current_movie);
    }
}

void IMDb::update_rating(std::string user_id, std::string movie_id,
                         int rating) {
    // Rating-ul se modifica, trebuie modificat map-ul de recent_movies
    rated_movies_up_to_date = false;
    double old_rating = movies[movie_id].update_rating(user_id, rating);
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
    // Rating-ul se modifica, trebuie modificat map-ul de recent_movies
    rated_movies_up_to_date = false;
    // Se schimba topul de popularitate
    popular_movies.clear();
    movie &current_movie = movies[movie_id];
    double old_rating = current_movie.remove_rating(user_id);
    if (current_movie.nr_ratings() == 0) {
        rated_movies.erase(current_movie.get_timestamp());
    }
}

std::string IMDb::get_rating(std::string movie_id) {
    if (movies.find(movie_id) != movies.end()) {
        if (!movies[movie_id].nr_ratings()) {
            return NONE;
        }

        double rating;
        std::string final_rating;
        std::stringstream stream;
        int temp_rating = (int)(movies[movie_id].get_rating() * 1000);

        if (temp_rating % 10 >= 5) {
            temp_rating += 10;
        }

        temp_rating /= 10;
        rating = (double)temp_rating / 100.0;
        stream << std::fixed << std::setprecision(2) << rating;
        final_rating = stream.str();
        return final_rating;
    }

    return NONE;
}

std::string IMDb::get_longest_career_actor() {
    if (max_years.get_id() != "") {
        return max_years.get_id();
    }
    return NONE;
}

std::string IMDb::get_most_influential_director() {
    if (max_coll.director_name != "") {
        return max_coll.director_name;
    }
    return NONE;
}

std::string IMDb::get_best_year_for_category(std::string category) {
    return "";
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
    // std::unordered_map<std::string, actor> &1st_degree, &2nd_degree;
    // std::map<std::string, actor> 2nd_degree_colleagues;
    // auto it = 1st_degree.begin();
    // 1st_degree = actors[actor_ids].get_colleagues();

    // for (; it != 1st_degree.end(); ++it) {
    //     2nd_degree = it->second.get_colleagues();
    //     auto it1 = 2nd_degree.begin();
    //     for (; it1 != 2nd_degree.end(); ++it1) {
    //         if (it1->second.check() == unchecked) {
    //             2nd_degree_colleagues.insert(*it1);
    //             it1->second.checking();
    //         }
    //     }
    // }
    return "";
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
    if (!recent_movies.empty()) {
        int i = 1;
        auto it = recent_movies.rbegin();
        std::string result = it->second.get_movie_id();
        ++it;
        for (it = it; i < k && it != recent_movies.rend(); ++it, ++i) {
            result += " " + it->second.get_movie_id();
        }
        return result;
    }

    return NONE;
}

std::string IMDb::get_top_k_actor_pairs(int k) {
    return "";
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id) {
    return "";
}

std::string IMDb::get_top_k_most_popular_movies(int k) {
    if (popular_movies.empty()) {
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            popular_movies.insert(it->second);
        }
    }

    if (popular_movies.empty()) {
        return NONE;
    }

    auto it = popular_movies.rbegin();
    std::string result = it->get_movie_id();
    ++it;
    --k;

    for (it = it; it != popular_movies.rend() && k; ++it, --k) {
        result += " " + it->get_movie_id();
    }

    return result;
}

std::string IMDb::get_avg_rating_in_range(int start, int end) {
    double rating = 0.0;
    int number_of_ratings = 0;

    if (rated_movies.empty()) {  // Daca nu exista filme cu rating, afisez none
        return NONE;
    }

    if (!rated_movies_up_to_date) {
        // Daca rated_movies nu e up to date, il updatez
        auto it = rated_movies.begin();
        int i = 1;

        // Primul element are suma rating-urilor egala cu rating-ul lui
        it->second.set_position(i++);
        it->second.set_rating_until_this(rating);
        rating = it->second.get_rating_until_this();
        ++it;

        for (it = it; it != rated_movies.end(); ++it) {
            // La urmatoarele elemente, suma rating-urilor este egala cu suma
            // rating-urilor elementului anterior + rating-ul sau
            it->second.set_position(i++);
            it->second.set_rating_until_this(rating);
            rating = it->second.get_rating_until_this();
        }
        rated_movies_up_to_date = true;  // rated_movies este acum up to date
    }

    // Cautare binara a intervalului din rated_movies in care se afla
    // elementele dintre start si end
    auto lower = rated_movies.lower_bound(start);
    auto upper = rated_movies.upper_bound(end);

    if (lower == upper) {  // Daca nu am elemente in intervalul (start, end)
        return NONE;
    }

    --upper;  // Pun iteratorul upper pe ultimul element din interval

    // Rating-ul este suma rating-urilor pana la ultimul element din interval
    // scazut cu suma rating-urilor pana la primului element din interval si
    // adunat cu rating-ul primului element (Deoarece a fost scazut), totul
    // impartit la numarul de rating-uri.
    rating = upper->second.get_rating_until_this() + lower->second.get_rating()
            - lower->second.get_rating_until_this();
    // Intr-un interval [a, b] sunt b - a + 1 elemente, deci numarul de
    // rating-uri este pozitia ultimului - pozitia primului + 1
    number_of_ratings = upper->second.get_position() + 1
                       - lower->second.get_position();

    rating /= number_of_ratings;

    // Aproximez la 2 zecimale
    std::stringstream stream;
    std::string result;

    stream << std::fixed << std::setprecision(2) << rating;
    result = stream.str();

    return result;
}
