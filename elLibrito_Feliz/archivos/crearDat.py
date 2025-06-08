import struct

libros_raw = """
9780743499484,The Dead Yard,Adrian McKinty,2006-05-03,1,0
9780006499626,Miss Marple,Agatha Christie,1997-07-24,2,0
9780007113804,Murder in Mesopotamia,Agatha Christie,2001-02-07,3,0
9780007119332,Death in the Clouds,Agatha Christie,2001-03-08,5,0
9780007119356,Appointment with Death,Agatha Christie,2001-04-09,4,0
9780007120819,The Big Four,Agatha Christie,2002-05-10,1,0
9780007120864,The Thirteen Problems,Agatha Christie,2002-08-25,3,0
9780007120963,A Murder is Announced,Agatha Christie,2002-09-26,5,0
9780007121014,Taken at the Flood,Agatha Christie,2002-06-04,6,0
9780007121021,The Hollow,Agatha Christie,2002-06-11,6,0
9780007151677,Endless Night,Agatha Christie,2002-07-05,2,0
9780007154845,The Mysterious Mr. Quin,Agatha Christie,2003-07-12,2,0
9780007154883,The Listerdale Mystery,Agatha Christie,2003-08-13,3,0
9780312970079,Black Coffee,Agatha Christie,1999-08-06,3,0
9780312981662,Crooked House,Agatha Christie,2002-09-07,5,0
9780399150210,Hercule Poirots Casebook,Agatha Christie,1989-09-14,5,0
9780425100417,The Regatta Mystery and Other Stories,Agatha Christie,1984-10-08,4,0
9780425200452,Murder on the Orient Express,Agatha Christie,2004-11-09,1,0
9781579126230,Murder on the Orient Express,Agatha Christie,1934-12-10,6,0
9781579126247,The A.B.C. Murders,Agatha Christie,1936-01-11,2,0
9781579126254,Murder at the Vicarage,Agatha Christie,2005-02-12,3,0
9781579126261,The Body in the Library,Agatha Christie,2006-03-13,5,0
9781579126278,The Murder of Roger Ackroyd,Agatha Christie,1926-04-14,4,0
9781579126285,Evil Under the Sun,Agatha Christie,1940-05-15,1,0
9781579126292,A Murder is Announced,Agatha Christie,2005-06-16,6,0
9781579126896,Death on the Nile,Agatha Christie,2007-07-17,2,0
9781579126957,The Mystery of the Blue Train,Agatha Christie,1928-08-18,3,0
9780345495846,Logs Seven and Eight,Alan Dean Foster,2006-09-19,5,0
9780441248834,Betcha Cant Read Just One,Alan Dean Foster,1993-10-20,4,0
9780671854058,Star Trek,Alan Dean Foster,1995-08-10,3,0
9780140286373,The Spell,Alan Hollinghurst,2000-11-21,1,0
9781582346106,The Line of Beauty,Alan Hollinghurst,2005-12-22,6,0
9781400077809,Einsteins Dreams,Alan P. Lightman,1993-01-23,2,0
9780743262170,Cry the Beloved Country,Alan Paton,1987-02-24,3,0
9780141185132,The Plague,Albert Camus,2002-04-02,4,0
9780679720225,The Fall,Albert Camus,1956-03-25,5,0
9780679764014,Resistance Rebellion and Death,Albert Camus,1961-04-26,4,0
9781400042555,The Plague,Albert Camus,2004-05-27,1,0
9780060085490,Island,Aldous Huxley,1962-06-28,6,0
9780060776091,Brave New World and Brave New World Revisited,Aldous Huxley,2005-07-29,2,0
9780060850524,Brave New World,Aldous Huxley,2006-08-30,3,0
9780060929879,Brave New World,Aldous Huxley,1998-9-31,5,0
9781564781314,Point Counter Point,Aldous Huxley,2001-10-01,4,0
9781566630184,After Many a Summer Dies the Swan,Aldous Huxley,1993-11-02,1,0
9781790877799,The Perfume Factory,Alex Austin,2018-09-11,5,0
9780898709193,No Price Too High,Alex Jones,2006-01-25,2,0
9781400031368,Morality for Beautiful Girls,Alexander McCall Smith,2002-12-03,6,0
9781400034772,The No. 1 Ladies Detective Agency,Alexander McCall Smith,2002-01-04,2,0
9781400075706,In the Company of Cheerful Ladies,Alexander McCall Smith,2006-02-05,3,0
9781400075713,Blue Shoes and Happiness,Alexander McCall Smith,2007-03-06,5,0
9781400077090,The Sunday Philosophy Club,Alexander McCall Smith,2005-04-07,4,0
9781400095087,The Finer Points of Sausage Dogs,Alexander McCall Smith,2003-05-08,1,0
9780140449778,The Womens War,Alexandre Dumas,2006-06-09,6,0
9780812969634,The Knight Of MaisonRouge,Alexandre Dumas,2004-07-10,2,0
9781853260407,The Three Musketeers,Alexandre Dumas,1993-08-11,3,0
9780231085076,Discovering Plato,Alexandre Koyre,1960-10-12,4,0
9780425196847,Janes Warlord,Angela Knight,2004-09-12,5,0
9780425198803,Master of the Night,Angela Knight,2004-10-13,4,0
9780425203576,Master of the Moon,Angela Knight,2005-11-14,1,0
9780425209219,Master of Swords,Angela Knight,2006-12-15,6,0
9780425214244,Master of Dragons,Angela Knight,2007-01-16,2,0
9780618056804,Baumgartners Bombay,Anita Desai,2000-02-17,3,0
9780618074518,Clear Light of Day,Anita Desai,2000-03-18,5,0
9788122200850,Cry the Peacock,Anita Desai,1980-04-19,4,0
9780312353766,The Red Tent,Anita Diamant,2005-05-20,1,0
9781555916220,The Gonzo Way,Anita Thompson,2007-02-26,3,0
9780679732341,Chilly Scenes of Winter,Ann Beattie,1991-06-21,6,0
9780373760039,The Accidental Bodyguard,Ann Major,1996-07-22,2,0
9780743466523,Fall on Your Knees,Ann Marie MacDonald,2002-12-20,6,0
9781562802349,The Other Woman,Ann OLeary,1999-08-23,3,0
9780375727139,The Dive from Clausens Pier,Ann Packer,2003-09-24,5,0
9780373712489,Her Little Secret,Anna Adams,2005-10-25,4,0
9780385333139,Black and Blue,Anna Quindlen,2000-11-26,1,0
9780738546780,Selections from the Oakland Tribune Archives,Annalee Allen,2006-07-22,2,0
9780385508476,The Diary of Anne Frank,Anne Frank,2003-08-23,3,0
9780415901475,Mary Shelley,Anne Kostelanetz Mellor,1988-03-27,5,0
9780385496094,Traveling Mercies,Anne Lamott,2000-04-28,4,0
9781594481574,Plan B,Anne Lamott,2006-05-29,1,0
9780385337816,Coming of Age in Mississippi,Anne Moody,1968-06-30,6,0
9780099271499,Blood and Gold,Anne Rice,2002-12-27,6,0
9780345396938,Cry to Heaven,Anne Rice,1995-01-28,2,0
9780345419620,The Queen of the Damned,Anne Rice,1997-02-29,3,0
9780345419637,The Tale of the Body Thief,Anne Rice,1997-03-30,5,0
9780345422408,Merrick,Anne Rice,2001-04-31,4,0
9780345456342,The Vampire Chronicles Collection,Anne Rice,2002-05-01,1,0
9780345476883,The Vampire Lestat,Anne Rice,2004-06-02,6,0
9780380776047,To Love a Dark Lord,Anne Stuart,1994-07-03,2,0
9780451192523,Ritual Sins,Anne Stuart,1997-08-04,3,0
9780451408693,Shadow Lover,Anne Stuart,1999-09-05,5,0
9780778321712,Black Ice,Anne Stuart,2005-10-06,4,0
9780778323563,Cold as Ice,Anne Stuart,2006-11-07,1,0
9780778324782,Ice Blue,Anne Stuart,2007-12-08,6,0
9780821760536,Prince of Magic,Anne Stuart,1998-01-09,2,0
9781551665719,Shadows at Sunset,Anne Stuart,2000-02-10,3,0
9780345472458,The Amateur Marriage,Anne Tyler,2006-03-11,5,0
9780345478955,A Slippingdown Life,Anne Tyler,1970-04-12,4,0
9780449911891,The Tin Can Tree,Anne Tyler,1996-05-13,1,0
9780804119184,A Patchwork Planet,Anne Tyler,2001-06-14,6,0
9780060915186,An American Childhood,Annie Dillard,1988-07-31,2,0
9780060920647,Three by Annie Dillard,Annie Dillard,1990-07-15,2,0
9780020360759,Heart Songs and Other Stories,Annie Proulx,1995-08-16,3,0
9780684852225,Close Range,Annie Proulx,2000-09-17,5,0
9780743271325,Brokeback Mountain,Annie Proulx,2005-10-18,4,0
9780373126002,A Mistress For The Taking,Annie West,2007-11-19,1,0
9780312426118,A Woman in Berlin,Anonymous,2006-08-01,3,0
9780060899226,Kitchen Confidential Updated Ed,Anthony Bourdain,2007-09-02,5,0
9780060934910,Kitchen Confidential,Anthony Bourdain,2000-10-03,4,0
9780099468646,Earthly Powers,Anthony Burgess,2004-01-21,2,0
9780393315080,The Wanting Seed,Anthony Burgess,1963-02-22,3,0
9780393316025,The Doctor Is Sick,Anthony Burgess,1997-03-23,5,0
9780091895815,The Toy Maker,Anthony McReavy,2004-11-04,1,0
9780226677149,A Dance to the Music of Time,Anthony Powell,1995-04-24,4,0
9780553381009,Stories,Anton Pavlovich Chekhov,2000-05-25,1,0
9781400032921,The Complete Short Novels,Anton Pavlovich Chekhov,2005-06-26,6,0
9781593080037,Ward No. 6 and Other Stories,Anton Pavlovich Chekhov,2003-07-27,2,0
9780385489492,Marie Antoinette,Antonia Fraser,2001-12-05,6,0
9781556526442,The Winthrop Woman,Anya Seton,2006-08-28,3,0
9780060964047,Tales of the City,Armistead Maupin,1989-09-29,5,0
9780375408274,Ralph Ellison,Arnold Rampersad,2007-01-06,2,0
9780312878603,The Collected Stories of Arthur C. Clarke,Arthur C. Clarke,2002-10-30,4,0
9780345452511,Sunstorm,Arthur Charles Clarke,2006-11-31,1,0
9780393058000,The Novels,Arthur Conan Doyle,2005-11-28,1,0
9780393059168,The New Annotated Sherlock Holmes,Arthur Conan Doyle,2005-10-27,4,0
9780451528018,The Hound of the Baskervilles,Arthur Conan Doyle,2001-12-01,6,0
9780803266551,The Coming of the Fairies,Arthur Conan Doyle,2006-02-03,3,0
9781551117225,The Hound of the Baskervilles,Arthur Conan Doyle,2006-03-04,5,0
9780766144736,Arthur Edward Waites Quest of the Golden Stairs,Arthur Edward Waite,2003-04-05,4,0
9780670261550,Death of a Salesman,Arthur Miller,1967-05-06,1,0
9780671027636,The Fuck Up,Arthur Nersesian,1999-06-07,6,0
9780060977498,The God of Small Things,Arundhati Roy,1998-07-08,2,0
9780425199435,The Glass House,Ashley Gardner,2004-08-09,3,0
9780452281257,Anthem,Ayn Rand,1999-09-10,5,0
9780525948926,Atlas Shrugged,Ayn Rand,2005-10-11,4,0
9780786811052,Sparrow Hawk Red,Ben Mikaelsen,1995-03-03,5,0
9781564782991,Heartsnatcher,Boris Vian,2003-11-12,1,0
9780393970128,Dracula,Bram Stoker,1997-12-13,6,0
9780743477369,Dracula,Bram Stoker,2003-01-14,2,0
9780800809638,The Bram Stoker Bedside Companion,Bram Stoker,1973-02-15,3,0
9780800783365,The Screwtape LettersBook & Study Guide,C. S. Lewis,1978-11-13,1,0
9781931082037,Collected Works of Carson McCullers,Carson McCullers,2017-12-14,6,0
9780061131271,Factotum tiein,Charles Bukowski,2006-03-16,5,0
9780061177590,Women,Charles Bukowski,2007-04-17,4,0
9780876851388,Mockingbird Wish Me Luck,Charles Bukowski,2002-05-18,1,0
9780876856833,You Get So Alone at Times,Charles Bukowski,2002-06-19,6,0
9780140436143,Martin Chuzzlewit,Charles Dickens,1999-07-20,2,0
9780140439052,A Christmas Carol and Other Christmas Writings,Charles Dickens,2003-08-21,3,0
9780141439600,A Tale of Two Cities,Charles Dickens,2003-09-22,5,0
9780141439969,Little Dorrit,Charles Dickens,2003-10-23,4,0
9780192806949,A Christmas Carol and Other Christmas Books,Charles Dickens,2006-11-24,1,0
9780192833594,Great Expectations,Charles Dickens,1998-12-25,6,0
9780375757013,Great Expectations,Charles Dickens,2001-01-26,2,0
9780375759147,Little Dorrit,Charles Dickens,2002-02-27,3,0
9780393051582,The Annotated Christmas Carol,Charles Dickens,2004-03-28,5,0
9780451530042,David Copperfield,Charles Dickens,2006-04-29,4,0
9780486424538,Oliver Twist,Charles Dickens,2002-05-30,1,0
9780517093399,Four Novels,Charles Dickens,1993-6-31,6,0
9781580495790,A Christmas Carol,Charles Dickens,2005-07-01,2,0
9780002261982,Spiders Web,Charles Osborne,2000-10-15,4,0
9780345484291,Tsubasa 9 Reservoir Chronicle,CLAMP (Mangaka group),2004-01-15,2,0
9780743449670,Shock Wave,Clive Cussler,2002-04-04,4,0
9780517168950,The Crossing,Cormac McCarthy,1996-02-16,3,0
9780140437850,A Journal of the Plague Year,Daniel Defoe,2003-08-02,3,0
9780141439822,Robinson Crusoe,Daniel Defoe,2003-09-03,5,0
9781853260735,Moll Flanders,Daniel Defoe,1993-10-04,4,0
9780553213447,Divine Comedy  Purgatorio,Dante Alighieri,1988-03-17,5,0
9780968394731,The Wealthy Barber,David Barr Chilton,2002-11-14,1,0
9780761501664,The Wealthy Barber,David Chilton,1996-12-15,6,0
9780375836572,The Realm of Possibility,David Levithan,2006-09-24,5,0
9780375839566,Are We There Yet?,David Levithan,2007-10-25,4,0
9780439890281,This is Push,David Levithan,2007-11-26,1,0
9780618439096,Dunk,David Lubar,2004-12-27,6,0
9780765345707,In the Land of the Lawn Weenies,David Lubar,2003-01-28,2,0
9780765357663,Hidden Talents,David Lubar,2007-2-29,3,0
9780395746561,Sector 7,David Wiesner,1999-03-30,5,0
9780099911708,Cross Stitch,Diana Gabaldon,1992-05-20,1,0
9780385302319,Dragonfly in Amber,Diana Gabaldon,1992-11-05,1,0
9780385335973,Dragonfly in Amber,Diana Gabaldon,2001-12-06,6,0
9780385335997,Voyager,Diana Gabaldon,2001-01-07,2,0
9780385340397,A Breath of Snow and Ashes,Diana Gabaldon,2006-02-08,3,0
9780440221661,The Fiery Cross,Diana Gabaldon,2005-03-09,5,0
9780440242949,Outlander,Diana Gabaldon,2005-04-10,4,0
9780517119129,Two Complete Novels,Douglas Adams,1987-01-30,2,0
9780007158522,Oh the Places Youll Go!,Dr. Seuss,2003-05-05,1,0
9780385074070,Complete Stories and Poems of Edgar Allan Poe,Edgar Allan Poe,1966-05-11,1,0
9780440322276,18 Best Stories,Edgar Allan Poe,1965-06-12,6,0
9780679643425,The Murders in the Rue Morgue,Edgar Allan Poe,2006-07-13,2,0
9780785814535,Edgar Allan Poe Complete Tales and Poems,Edgar Allan Poe,2009-08-14,3,0
9780152758516,The Sleeping Giant and Other Stories,Eleanor Estes,1948-04-19,4,0
9781842163863,Portrait of Dorian Gray,Elizabeth Gray,2000-02-31,3,0
9780312321185,Something Borrowed,Emily Giffin,2004-09-15,5,0
9780312321192,Something Borrowed,Emily Giffin,2005-10-16,4,0
9780312323868,Something Blue,Emily Giffin,2006-11-17,1,0
9780312348649,Baby Proof,Emily Giffin,2006-12-18,6,0
9780156007474,Slammerkin,Emma Donoghue,2000-01-19,2,0
9781555837235,Stirfry,Emma Donoghue,1994-02-20,3,0
9780425212592,Prince of Ice,Emma Holly,2006-03-21,5,0
9780515133080,Beyond Seduction,Emma Holly,2002-04-22,4,0
9780671455279,Sweet and Low,Emma Lathen,1982-05-23,1,0
9780340796146,Five on a Treasure Island,Enid Blyton,2001-06-06,6,0
9780340917541,The Secret Seven,Enid Blyton,2006-01-01,2,0
9780345020321,A Fish Dinner in Memison,Eric Rucker Eddison,1970-04-18,4,0
9780020518600,The Short Stories of Ernest Hemingway,Ernest Hemingway,1986-06-24,6,0
9780099339212,The First Fortynine Stories,Ernest Hemingway,1993-07-25,2,0
9780684804521,The Garden of Eden,Ernest Hemingway,1995-08-26,3,0
9780684830513,The Sun Also Rises,Ernest Hemingway,1996-09-27,5,0
9780684843322,The Complete Short Stories Of Ernest Hemingway,Ernest Hemingway,1998-10-28,4,0
9780684844640,Across the River and Into the Trees,Ernest Hemingway,1998-11-29,1,0
9780684859231,To Have and Have Not,Ernest Hemingway,1999-12-30,6,0
9780940450486,Complete Plays: 19321943,Eugene ONeill,1988-05-19,1,0
9780020199854,The Love of the Last Tycoon,F. Scott Fitzgerald,1994-01-31,2,0
9780141183596,Tender is the Night,F. Scott Fitzgerald,2001-02-01,3,0
9780521402408,Fitzgerald: All The Sad Young Men,F. Scott Fitzgerald,2007-03-02,5,0
9780684804422,The Pat Hobby Stories,F. Scott Fitzgerald,1995-04-03,4,0
9780684804453,The Short Stories of F. Scott Fitzgerald,F. Scott Fitzgerald,1995-05-04,1,0
9780891906797,The Great Gatsby,F. Scott Fitzgerald,1925-06-05,6,0
9781581342147,This Present Darkness ; Piercing the Darkness,Frank E. Peretti,1997-06-20,6,0
9781581345261,Prophet,Frank E. Peretti,2004-07-06,2,0
9781581345278,Piercing the Darkness,Frank E. Peretti,2003-08-07,3,0
9781581345285,This Present Darkness,Frank E. Peretti,2003-09-08,5,0
9781595540454,The Oath,Frank E. Peretti,2005-10-09,4,0
9780441102679,Chapterhouse: Dune,Frank Herbert,1987-11-10,1,0
9780765342515,The Santaroga Barrier,Frank Herbert,2002-12-11,6,0
9780765342522,The Eyes of Heisenberg,Frank Herbert,2002-01-12,2,0
9780765342539,The Dosadi Experiment,Frank Herbert,2002-02-13,3,0
9781557832450,Springs Awakening,Frank Wedekind,1995-03-14,5,0
9780099428640,The Trial,Franz Kafka,2001-04-15,4,0
9780684800707,The Metamorphosis,Franz Kafka,2000-05-16,1,0
9780805210552,The Complete Stories,Franz Kafka,1995-06-17,6,0
9780671878849,Berserkers,Fred Saberhagen,1998-07-18,2,0
9780812505771,The Last Book of Swords: Shieldbreakers Story,Fred Saberhagen,1995-08-19,3,0
9780812511185,The Sixth Book of Lost Swords,Fred Saberhagen,1991-09-20,5,0
9780812522839,An Armory of Swords,Fred Saberhagen,1996-10-21,4,0
9780812552843,The Fourth Book of Lost Swords,Fred Saberhagen,1990-11-22,1,0
9780812590463,Ariadnes Web,Fred Saberhagen,2001-12-23,6,0
9780192835093,The Karamazov Brothers,Fyodor Dostoevsky,1998-02-25,3,0
9780374528379,The Brothers Karamazov,Fyodor Dostoevsky,2002-01-24,2,0
9780140442526,Notes from Underground,Fyodor Dostoyevsky,1972-03-26,5,0
9780140449242,The Brothers Karamazov,Fyodor Dostoyevsky,2003-04-27,4,0
9780375719004,The Adolescent,Fyodor Dostoyevsky,2004-05-28,1,0
9780486432137,The Idiot,Fyodor Dostoyevsky,2003-10-02,4,0
9780553212167,The Brothers Karamazov,Fyodor Dostoyevsky,1970-06-29,6,0
9780679420293,Crime and Punishment,Fyodor Dostoyevsky,1993-07-30,2,0
9780679734505,Crime and Punishment,Fyodor Dostoyevsky,1993-08-31,3,0
9781101487556,Crime and Punishment,Fyodor Dostoyevsky,2002-09-01,5,0
9780060531041,One Hundred Years of Solitude,Gabriel Garcia Marquez,2003-02-06,3,0
9780060882860,The Autumn of the Patriarch,Gabriel Garcia Marquez,2006-03-07,5,0
9780060932664,Collected Novellas,Gabriel Garcia Marquez,1999-04-08,4,0
9780060932688,Collected Stories,Gabriel Garcia Marquez,1999-05-09,1,0
9780061120091,One Hundred Years of Solitude,Gabriel Garcia Marquez,2006-06-10,6,0
9780606349154,One Hundred Years of Solitude,Gabriel Garcia Marquez,2006-08-12,3,0
9781400034680,Love in the Time of Cholera,Gabriel Garcia Marquez,2003-11-03,1,0
9781400034697,Strange Pilgrims,Gabriel Garcia Marquez,2006-12-04,6,0
9781400034710,Chronicle of a Death Foretold,Gabriel Garcia Marquez,2003-07-11,2,0
9781400043330,The General in His Labyrinth,Gabriel Garcia Marquez,2004-01-05,2,0
9780393092103,Middlemarch,George Eliot,1966-07-21,2,0
9780156701761,The Orwell Reader,George Orwell,1961-11-10,1,0
9780375415036,Essays,George Orwell,2002-12-11,6,0
9780436350238,The Complete Works of George Orwell,George Orwell,1986-08-22,3,0
9780553381696,A Clash of Kings,George R. R. Martin,2002-09-13,5,0
9780553582024,A Feast for Crows,George R. R. Martin,2006-10-14,4,0
9780812575231,Legends,George R. R. Martin,1999-12-16,6,0
9781592220045,Tuf Voyaging,George R. R. Martin,2003-11-15,1,0
9781594481529,The Brief and Frightening Reign of Phil,George Saunders,2005-01-17,2,0
9781840681123,Divine Filth,Georges Bataille,2004-02-18,3,0
9780140189865,Species of Spaces and Other Pieces,Georges Perec,1997-01-12,2,0
9780879237516,Life a Users Manual,Georges Perec,1987-03-19,5,0
9781567921588,W Or The Memory of Childhood,Georges Perec,2003-04-20,4,0
9781567922967,A Void,Georges Perec,2005-05-21,1,0
9780370307121,A Likely Lad,Gillian Avery,1986-07-07,2,0
9780439411370,The Summit,Gordon Korman,2002-4-31,4,0
9780439507226,The Discovery,Gordon Korman,2003-05-01,1,0
9780439507233,The Deep,Gordon Korman,2003-06-02,6,0
9780439651363,Chasing the Falconers,Gordon Korman,2005-07-03,2,0
9780439651370,The Fugitive Factor,Gordon Korman,2005-08-04,3,0
9780439651394,The Stowaway Solution,Gordon Korman,2005-09-05,5,0
9780439651400,Public Enemies,Gordon Korman,2005-10-06,4,0
9780439651417,Hunting the Hunter,Gordon Korman,2006-11-07,1,0
9780439847773,The Abduction,Gordon Korman,2006-12-08,6,0
9780439847797,The Rescue,Gordon Korman,2006-01-09,2,0
9780590255226,Something Fishy at Macdonald Hall,Gordon Korman,2000-02-10,3,0
9780590419277,Radio Fifth Grade,Gordon Korman,1991-03-11,5,0
9780786809196,Son of the Mob: Hollywood Hustle,Gordon Korman,2006-04-12,4,0
9780786815937,Son of the Mob,Gordon Korman,2004-05-13,1,0
9780099478423,The Heart of the Matter,Graham Greene,2004-06-22,6,0
9780140185331,The Third Man and the Fallen Idol,Graham Greene,1977-07-23,2,0
9780140186123,Collected Short Stories,Graham Greene,1986-08-24,3,0
9780142437308,The Power and the Glory,Graham Greene,2003-09-25,5,0
9780142437919,Stamboul Train,Graham Greene,2004-10-26,4,0
9780143039020,The quiet American,Graham Greene,1955-01-29,2,0
9780143039105,Complete Short Stories,Graham Greene,2005-11-27,1,0
9780671019099,The Tenth Man,Graham Greene,1998-12-28,6,0
9780451205551,Trauma,Graham Masterton,2002-2-30,3,0
9780843947465,The House That Jack Built,Graham Masterton,2000-03-31,5,0
9781844164035,The Ultramarines Omnibus,Graham McNeill,2008-04-01,4,0
9781563893698,JLA,Grant Morrison,1997-06-14,6,0
9780743480727,Blood Enemy,Greg Cox,2004-05-02,1,0
9780451206527,Dead Sleep,Greg Iles,2002-06-03,6,0
9780451207500,Trapped,Greg Iles,2002-07-04,2,0
9780743292498,True Evil,Greg Iles,2006-08-05,3,0
9780743454148,The Footprints of God,Greg Iles,2004-09-06,5,0
9780345446107,Edge of Victory II,Greg Keyes,2001-10-07,4,0
9780060546571,Three Rotten Eggs,Gregory Maguire,2005-07-15,2,0
9780060745905,Wicked Musical Tiein Edition,Gregory Maguire,2004-11-08,1,0
9780060747220,Son of a Witch,Gregory Maguire,2006-12-09,6,0
9780060760823,A Couple of April Fools,Gregory Maguire,2005-08-16,3,0
9780060987527,Confessions of an Ugly Stepsister,Gregory Maguire,2000-01-10,2,0
9780064405959,Seven Spiders Spinning,Gregory Maguire,1995-09-17,5,0
9780064408745,The Good Liar,Gregory Maguire,2002-10-18,4,0
9780064410724,Four Stupid Cupids,Gregory Maguire,2001-11-19,1,0
9780385335546,The Midwifes Tale,Gretchen Moran Laskas,2004-02-11,3,0
9780142000205,Icy Sparks,Gwyn Hyman Rubio,1998-03-12,5,0
9780812504675,The Invisible Man,H. G. Wells,1992-04-13,4,0
9780345350800,The Best of H.P. Lovecraft,H. P. Lovecraft,1982-05-14,1,0
9780345422040,Tales of the Cthulhu Mythos,H. P. Lovecraft,1998-06-15,6,0
9780141441115,TonoBungay,H.G. Wells,2005-08-17,3,0
9780375724930,The bridegroom,Ha Jin,2001-09-18,5,0
9780671797867,Scar Lover,Harry Crews,1993-10-19,4,0
9780688023720,Karate is a Thing of the Spirit,Harry Crews,1983-11-20,1,0
9780679767398,South of the Border West of the Sun,Haruki Murakami,2000-12-21,6,0
9781400079278,Kafka on the Shore,Haruki Murakami,2006-01-22,2,0
9781400096084,Blind Willow Sleeping Woman,Haruki Murakami,2007-02-23,3,0
9781860465819,The Windup Bird Chronicle,Haruki Murakami,1999-03-24,5,0
9780670032563,The New Spirit,Havelock Ellis,1970-10-24,4,0
9781416507819,Star Trek: Voyager: String Theory #3,Heather Jarman,2006-04-25,4,0
9780373766628,Blame it on the Blackout,Heidi Betts,2005-05-26,1,0
9780373767618,Bedded Then Wed,Heidi Betts,2006-06-27,6,0
9780373767793,Blackmailed Into Bed,Heidi Betts,2007-07-28,2,0
9780141000190,Bridget Joness Diary,Helen Fielding,2001-08-29,3,0
9780142000212,Bridget Joness Guide to Life,Helen Fielding,2001-09-30,5,0
9781400095810,Before the Frost,Henning Mankell,2006-10-31,4,0
9780393959055,Walden ; And Resistance to Civil Government,Henry David Thoreau,1992-02-13,3,0
9781853260216,The History of Tom Jones,Henry Fielding,1992-11-01,1,0
9780141439631,The Portrait of a Lady,Henry James,2003-12-02,6,0
9780141439907,The Turn of the Screw and The Aspern Papers,Henry James,2003-01-03,2,0
9780192834423,The Bostonians,Henry James,1998-02-04,3,0
9780192835437,Daisy Miller and Other Stories,Henry James,1998-03-05,5,0
9781590170786,The Ivory Tower,Henry James,2004-04-06,4,0
9781883011093,Complete Stories 18921898,Henry James,1996-03-14,5,0
9781931082303,Novels 18961899,Henry James,2003-05-07,1,0
9780486215310,Best Science Fiction Stories of H. G. Wells,Herbert George Wells,1966-04-15,4,0
9780895591326,Billy Budd,Herman Melville,1978-11-25,1,0
9780940450004,Typee,Herman Melville,1982-12-26,6,0
9780940450097,Redburn WhiteJacket MobyDick,Herman Melville,1983-01-27,2,0
9780679755487,The Death of Virgil,Hermann Broch,1995-06-08,6,0
9780312278496,The Glass Bead Game,Hermann Hesse,2002-07-09,2,0
9780312421687,The Journey to the East,Hermann Hesse,2003-08-10,3,0
9780553275865,Narcissus and Goldmund,Hermann Hesse,1971-09-11,5,0
9780553377767,The Fairy Tales of Hermann Hesse,Hermann Hesse,1995-10-12,4,0
9788173031014,Journey to the East,Hermann Hesse,2002-08-08,3,0
9780060931957,The Odyssey of Homer,Homer,1999-11-13,1,0
9780451527363,The Odyssey,Homer,1999-12-14,6,0
9781857150940,The Odyssey,Homer,1992-03-01,5,0
9780140442373,Rabouilleuse,Honoré de Balzac,1970-01-15,2,0
9781406506587,Lost Illusions,Honoré de Balzac,2006-02-16,3,0
9780140442052,Cousin Pons,Honore Balzac,2006-03-17,5,0
9780140442328,A Harlot High and Low,Honore Balzac,1970-04-18,4,0
9781904316343,Judas Pig,Horace Silver,2004-05-19,1,0
9780140430363,Three Gothic Novels,Horace Walpole,1968-07-21,2,0
9780192834409,The Castle of Otranto,Horace Walpole,1998-06-20,6,0
9780345331052,The Doom that Came to Sarnath,Howard Phillips Lovecraft,1971-08-22,3,0
9780345384225,The Transition of H.P. Lovecraft,Howard Phillips Lovecraft,1996-09-23,5,0
9781560252481,Requiem for a Dream,Hubert Selby,1999-10-24,4,0
9780671020828,The Gun Seller,Hugh Laurie,1998-11-25,1,0
9780684856476,The Rum Diary,Hunter S. Thompson,1999-12-26,6,0
9780684873206,Hey Rube,Hunter S. Thompson,2005-05-16,1,0
9780684873213,Screwjack,Hunter S. Thompson,2000-01-27,2,0
9780061053566,The Player of Games,Iain Banks,1997-02-28,3,0
9780553374599,Feersum Endjinn,Iain Banks,1995-03-29,5,0
9781597800440,The Algebraist,Iain M. Banks,2006-04-30,4,0
9781892389381,The State of the Art,Iain M. Banks,2005-05-31,1,0
9780425178928,The Raphael Affair,Iain Pears,2001-06-01,6,0
9781573229869,The Dream of Scipio,Iain Pears,2002-07-02,2,0
9781594481758,The Portrait,Iain Pears,2006-08-03,3,0
9780440241355,The Rule of Four,Ian Caldwell,2005-09-04,5,0
9780142003299,Octopussy,Ian Fleming,2004-10-05,4,0
9780340425626,From Russia with Love,Ian Fleming,1957-09-09,5,0
9780385721790,Atonement,Ian McEwan,2003-11-06,1,0
9780679749844,The Comfort of Strangers,Ian McEwan,2002-12-07,6,0
9781400076192,Saturday,Ian McEwan,2006-01-08,2,0
9780441014897,Magic Bites,Ilona Andrews,2007-02-09,3,0
9780743428187,The Twentieth Wife,Indu Sundaresan,2003-03-10,5,0
9780786711642,A Kiss Before Dying,Ira Levin,2003-04-11,4,0
9781400044733,Suite Francaise,Irene Nemirovsky,2006-05-12,1,0
9780140030341,The Nice and the Good,Iris Murdoch,1978-06-13,6,0
9780141186160,The Sea the Sea,Iris Murdoch,2001-07-14,2,0
9780141186177,A Fairly Honourable Defeat,Iris Murdoch,2001-08-15,3,0
9780141186696,The Bell,Iris Murdoch,2001-09-16,5,0
9780142180099,Nuns and Soldiers,Iris Murdoch,2002-10-17,4,0
9780060938109,The Schopenhauer Cure,Irvin Yalom,2006-11-18,1,0
9780393057249,Trainspotting,Irvine Welsh,2002-12-19,6,0
9780393315639,Marabou Stork Nightmares,Irvine Welsh,1997-01-20,2,0
9780393318685,Filth,Irvine Welsh,1998-02-21,3,0
9780451213235,The Agony and the Ecstasy,Irving Stone,1961-03-22,5,0
9780060556525,Gold,Isaac Asimov,2003-04-23,4,0
9780451450647,Robot Visions,Isaac Asimov,1991-05-24,1,0
9780553293425,Pebble in the Sky,Isaac Asimov,1991-06-25,6,0
9780553299496,The Robots of Dawn,Isaac Asimov,1994-07-26,2,0
9780553803709,I Robot,Isaac Asimov,2004-08-27,3,0
9780586008355,The Caves of Steel,Isaac Asimov,1993-09-28,5,0
9780374500528,Gimpel the Fool and Other Stories,Isaac Bashevis Singer,1988-10-29,4,0
9780374506803,The Slave,Isaac Bashevis Singer,1988-11-30,1,0
9780374517885,Sammlung,Isaac Bashevis Singer,1982-12-31,6,0
9780374524791,Satan in Goray,Isaac Bashevis Singer,1996-01-01,2,0
9780374530259,Gimpel the Fool,Isaac Bashevis Singer,1957-02-02,3,0
9780060924980,The Infinite Plan,Isabel Allende,1994-03-03,5,0
9780061120251,Daughter of Fortune,Isabel Allende,2006-04-04,4,0
9780061161575,Ines of My Soul LP,Isabel Allende,2006-05-05,1,0
9780553273915,The House of the Spirits,Isabel Allende,1986-06-06,6,0
9780842331913,Four Mothers at Chautauqua,Isabella Alden,1997-07-07,2,0
9780141187198,Seven Gothic Tales,Isak Dinesen,2002-08-08,3,0
9780156260558,Difficult Loves,Italo Calvino,1984-09-09,5,0
9780156453806,Invisible Cities,Italo Calvino,1978-10-10,4,0
9780156572040,Marcovaldo Or The Seasons in the City,Italo Calvino,1983-11-11,1,0
9780156659758,The Nonexistent Knight & The Cloven Viscount,Italo Calvino,1977-12-12,6,0
9780156949521,The Watcher & Other Stories,Italo Calvino,1975-01-13,2,0
9780192836892,First Love and Other Stories,Ivan Sergeevich Turgenev,1999-02-14,3,0
9780974607894,First Love,Ivan Sergeevich Turgenev,2004-03-15,5,0
9780140442243,Home of the Gentry,Ivan Turgenev,1970-04-16,4,0
9780140445220,Sketches from a Hunters Album,Ivan Turgenev,1990-05-17,1,0
9780671024819,Wither,J G Passarella,2000-06-18,6,0
9780345396709,Waterborn,J. Gregory Keyes,1997-07-19,2,0
9780802141682,Layer Cake,J. J. Connolly,2004-08-20,3,0
9780439064866,Harry Potter and the Chamber of Secrets,J. K. Rowling,2015-09-27,5,0
9780439358071,Harry Potter and the Order of the Phoenix,J. K. Rowling,2015-10-28,4,0
9780439554893,Harry Potter and the Chamber of Secrets,J. K. Rowling,2003-03-23,5,0
9780439554930,Harry Potter and the Sorcerers Stone,J. K. Rowling,2015-11-29,1,0
9780439655484,Harry Potter and the Prisoner of Azkaban,J. K. Rowling,2015-12-30,6,0
9780439682589,Harry Potter,J. K. Rowling,2004-12-20,6,0
9780439785969,Harry Potter and the HalfBlood Prince,J. K. Rowling,2015-01-31,2,0
9780439827607,The Harry Potter Collection,J. K. Rowling,2005-01-21,2,0
9780747546245,Harry Potter and the Goblet of Fire,J. K. Rowling,2000-02-22,3,0
9780140275650,Age of Iron,J. M. Coetzee,1998-09-21,5,0
9780140283358,Waiting for the Barbarians,J. M. Coetzee,1980-10-22,4,0
9780142002001,Youth,J. M. Coetzee,2003-11-23,1,0
9780261102309,The Lord of the Rings,J. R. R. Tolkien,1991-12-24,6,0
9780345345066,The Tolkien Reader,J. R. R. Tolkien,1986-01-25,2,0
9780395647417,The Lord of the Rings,J. R. R. Tolkien,1992-04-28,4,0
9780618153978,The Lord of the Rings,J. R. R. Tolkien,2001-02-26,3,0
9780618346257,The Fellowship of the Ring,J. R. R. Tolkien,2003-03-27,5,0
9781857234022,A Man Betrayed,J. V. Jones,1996-10-10,4,0
9780439227148,The Call of the Wild,Jack London,2000-04-24,4,0
9780517309803,Works of Jack London,Jack London,1980-11-11,1,0
9780719566226,Maisie Dobbs,Jacqueline Winspear,2005-11-16,1,0
9780313309335,The Fantastic Vampire,James Craig Holte,2002-12-28,6,0
9780140150308,The Portable James Joyce,James Joyce,1985-06-17,6,0
9780140247749,Dubliners,James Joyce,1996-09-02,5,0
9780141182803,Ulysses,James Joyce,2000-05-29,1,0
9780192839992,Dubliners,James Joyce,2000-06-30,6,0
9780451530158,A Portrait of the Artist as a Young Man,James Joyce,2006-07-31,2,0
9780517618875,The Portable James Joyce,James Joyce,1947-08-01,3,0
9780141439518,Pride and Prejudice,Jane Austen,2003-10-03,4,0
9780141439587,Emma,Jane Austen,2002-11-04,1,0
9780141439808,Mansfield Park,Jane Austen,2003-12-05,6,0
9780143039501,The Complete Novels,Jane Austen,2006-01-06,2,0
9780192802378,Emma,Jane Austen,2003-08-05,3,0
9780192802385,Pride and Prejudice,Jane Austen,2004-02-07,3,0
9780192802637,Persuasion,Jane Austen,2004-03-08,5,0
9780192802644,Mansfield Park,Jane Austen,2003-09-06,5,0
9780192832979,Jane Austens Letters,Jane Austen,1997-04-09,4,0
9780393977516,Sense and Sensibility,Jane Austen,2002-05-10,1,0
9780517147689,The Complete Novels,Jane Austen,1981-06-11,6,0
9781593080495,Sense and Sensibility,Jane Austen,2003-07-12,2,0
9781593081256,Sense and Sensibility,Jane Austen,2004-08-13,3,0
9780380755691,Silver Nights,Jane Feather,2001-09-14,5,0
9780553572490,Vice,Jane Feather,1996-10-15,4,0
9780140276909,Jemima J.,Jane Green,1998-11-16,1,0
9780140295948,Spellbound,Jane Green,2003-12-17,6,0
9780670034802,Swapping Lives,Jane Green,2005-01-18,2,0
9780767905206,Mr. Maybe,Jane Green,2002-02-19,3,0
9780767907811,Bookends,Jane Green,2003-03-20,5,0
9780767912242,Babyville,Jane Green,2004-04-21,4,0
9780767912273,To Have and to Hold,Jane Green,2004-05-22,1,0
9780821778067,This Christmas,Jane Green,2005-06-23,6,0
9780312982867,True Believers,Jane Haddam,2002-07-24,2,0
9780385265706,The Book of Ruth,Jane Hamilton,1990-08-25,3,0
9780385720106,A Map of the World,Jane Hamilton,1995-09-26,5,0
9780785282099,The Guardian,Jane Hamilton,1994-10-27,4,0
9780767916912,Love @ First Site,Jane Moore,2006-11-28,1,0
9780373124183,The Sultans Bought Bride,Jane Porter,2004-12-29,6,0
9780385721059,Good Faith,Jane Smiley,2004-01-30,2,0
9780385721875,The Age of Grief,Jane Smiley,2002-2-31,3,0
9780804119436,Horse Heaven,Jane Smiley,2003-04-02,4,0
9781400033836,A Thousand Acres,Jane Smiley,2003-05-03,1,0
9781400040612,Ten Days in the Hills,Jane Smiley,2007-06-04,6,0
9781400095469,The Greenlanders,Jane Smiley,2005-07-05,2,0
9781887726092,Tolkien on film,Janet Brennan Croft,2004-10-07,4,0
9780060584023,Metro Girl,Janet Evanovich,2005-08-06,3,0
9780060584030,Motor Mouth,Janet Evanovich,2006-09-07,5,0
9780060598808,Thanksgiving,Janet Evanovich,2006-10-08,4,0
9780060598846,Love Overboard,Janet Evanovich,2005-11-09,1,0
9780060598853,Back to the Bedroom,Janet Evanovich,2005-12-10,6,0
9780060598891,The Rocky Road to Romance,Janet Evanovich,2004-01-11,2,0
9780312203030,High Five,Janet Evanovich,1999-02-12,3,0
9780312306342,Plum Lovin,Janet Evanovich,2007-03-13,5,0
9780312349493,Lean Mean Thirteen,Janet Evanovich,2007-04-14,4,0
9780312362966,More Plums in One,Janet Evanovich,2007-05-15,1,0
9780312948962,Two for the Dough,Janet Evanovich,2007-06-16,6,0
9780312966973,Four to Score,Janet Evanovich,1999-07-17,2,0
9780312980146,Seven Up,Janet Evanovich,2002-08-18,3,0
9780312983864,Hard Eight,Janet Evanovich,2003-09-19,5,0
9780312985349,Eleven on Top,Janet Evanovich,2006-10-20,4,0
9781569471241,Robert Van Gulik,Janwillem Van de Wetering,1987-11-08,1,0
9780231121002,The Vital Illusion,Jean Baudrillard,2000-12-09,6,0
9780192822758,Confessions,Jean Jacques Rousseau,2000-01-10,2,0
9780874518252,Julie Or The New Heloise,Jean Jacques Rousseau,1997-02-11,3,0
9780865165465,The Evolution of the Gilgamesh Epic,Jeffrey H. Tigay,2002-03-12,5,0
9780306808906,Hemingway,Jeffrey Meyers,1999-07-18,2,0
9780878056262,Conversations with Jerzy Kosinski,Jerzy Kosinski,1993-04-13,4,0
9780140447200,Maxims and Reflections,Johann Goethe,2005-08-19,3,0
9781414306346,Looking for God in Harry Potter,John Granger,2006-05-14,1,0
9780099134015,A Time to Kill,John Grisham,1992-11-21,1,0
9780385337939,A Painted House,John Grisham,2004-12-22,6,0
9780385339087,The Client,John Grisham,2005-01-23,2,0
9780385339094,The Street Lawyer,John Grisham,2005-02-24,3,0
9780385339599,The Summons,John Grisham,2005-03-25,5,0
9780385339605,The Rainmaker,John Grisham,2005-04-26,4,0
9780385339650,The King of Torts,John Grisham,2005-05-27,1,0
9780385339667,The Chamber,John Grisham,2005-06-28,6,0
9780385339674,The Brethren,John Grisham,2005-07-29,2,0
9780385339698,The Runaway Jury,John Grisham,2006-08-30,3,0
9780385339704,The Pelican Brief,John Grisham,2006-9-31,5,0
9780440234746,The Testament,John Grisham,2000-10-01,4,0
9780582418271,The Firm,John Grisham,1999-11-02,1,0
9780374280390,Uncommon Carriers,John McPhee,2006-09-20,5,0
9780374516000,Giving Good Weight,John McPhee,1994-10-21,4,0
9780192804099,The Major Works,John Milton,2003-06-15,6,0
9780393924282,Paradise Lost,John Milton,2005-07-16,2,0
9780395809990,The Riverside Milton,John Milton,1998-11-22,1,0
9780521498678,The Cambridge Companion to Jane Austen,John O. Jordan,1997-08-17,3,0
9780007105045,Tree and Leaf,John Ronald Reuel Tolkien,2001-12-23,6,0
9780007173020,The Silmarillion,John Ronald Reuel Tolkien,2004-03-18,5,0
9780345375216,The Book of Lost Tales,John Ronald Reuel Tolkien,1992-01-04,2,0
9780345538376,The Hobbit  The Lord of the Rings,John Ronald Reuel Tolkien,2012-02-05,3,0
9780395606490,Sauron Defeated,John Ronald Reuel Tolkien,1992-03-06,5,0
9780395680926,Morgoths Ring: The legends of Aman,John Ronald Reuel Tolkien,1993-04-07,4,0
9780395710418,The War of the Jewels,John Ronald Reuel Tolkien,1994-05-08,1,0
9780395957998,Roverandom,John Ronald Reuel Tolkien,1998-06-09,6,0
9780618002238,The Two Towers,John Ronald Reuel Tolkien,1994-07-10,2,0
9780618009367,Farmer Giles of Ham,John Ronald Reuel Tolkien,1999-08-11,3,0
9780618083558,The History of the Lord of the Rings,John Ronald Reuel Tolkien,2000-01-16,2,0
9780618083572,The Return of the Shadow,John Ronald Reuel Tolkien,2000-02-17,3,0
9780618260584,The Lord of the Rings,John Ronald Reuel Tolkien,2002-09-12,5,0
9780618574957,The Two Towers,John Ronald Reuel Tolkien,2004-10-13,4,0
9780618894642,Children of Húrin,John Ronald Reuel Tolkien,2007-11-14,1,0
9781594130076,The Fellowship of the Ring,John Ronald Reuel Tolkien,2003-12-15,6,0
9780425152898,Mind Prey,John Sandford,1996-04-19,4,0
9780425182871,Chosen Prey,John Sandford,2002-05-20,1,0
9780425214435,Eyes of Prey,John Sandford,2007-06-21,6,0
9780345467324,Perfect Nightmare,John Saul,2006-07-22,2,0
9780345487032,The Devils Labyrinth,John Saul,2007-08-23,3,0
9780345490643,The Manhattan Hunt Club,John Saul,2006-09-24,5,0
9780440182931,Suffer the Children,John Saul,1989-10-25,4,0
9780449006535,Midnight Voices,John Saul,2003-11-26,1,0
9780449227947,Asylum,John Saul,1997-12-27,6,0
9780517182468,Three Terrifying Bestselling Novels,John Saul,1996-01-28,2,0
9780553173871,All Fall Down,John Saul,1991-2-29,3,0
9780553284119,Creature,John Saul,1990-03-30,5,0
9780553560275,Shadows,John Saul,1993-4-31,4,0
9780140177398,Of Mice and Men,John Steinbeck,1993-05-01,1,0
9780141185118,Tortilla Flat,John Steinbeck,2000-06-02,6,0
9780142000656,East of Eden,John Steinbeck,2002-07-03,2,0
9780142000687,Cannery Row,John Steinbeck,2002-08-04,3,0
9780143039433,The Grapes of Wrath,John Steinbeck,1939-09-05,5,0
9780613996983,East of Eden,John Steinbeck,1992-10-06,4,0
9780451217769,A Certain Justice,John T. Lescroart,2006-11-07,1,0
9780307264657,Terrorist,John Updike,2006-12-08,6,0
9780449911945,Rabbit at Rest,John Updike,1996-01-09,2,0
9780679444596,Rabbit Angstrom,John Updike,1995-02-10,3,0
9780764937101,The Twelve Terrors of Christmas,John Updike,2006-03-11,5,0
9780312873110,The Land of Laughs,Jonathan Carroll,2001-04-12,4,0
9780765311801,Glass Soup,Jonathan Carroll,2006-05-13,1,0
9780765311856,Outside the Dog Museum,Jonathan Carroll,2005-06-14,6,0
9780765311863,Sleeping in Flame,Jonathan Carroll,2004-07-15,2,0
9780007153589,How to be Alone,Jonathan Franzen,2004-01-24,2,0
9780312420147,The TwentySeventh City,Jonathan Franzen,2001-08-16,3,0
9781841157481,The Twentyseventh City,Jonathan Franzen,2003-12-17,6,0
9780156028974,Gun with Occasional Music,Jonathan Lethem,2003-09-17,5,0
9780375700125,As She Climbed Across the Table,Jonathan Lethem,1998-10-18,4,0
9781400076819,The Disappointment Artist,Jonathan Lethem,2006-02-25,3,0
9780060792176,Everything Is Illuminated tiein,Jonathan Safran Foer,2005-11-19,1,0
9780618711659,Extremely Loud and Incredibly Close,Jonathan Safran Foer,2006-12-20,6,0
9780486287591,A Modest Proposal and Other Satirical Works,Jonathan Swift,1996-03-26,5,0
9780811209052,Seven Nights,Jorge Luis Borges,1984-04-27,4,0
9780811214001,Everything and Nothing,Jorge Luis Borges,1999-05-28,1,0
9780156005203,Baltasar and Blimunda,Jose Saramago,1998-05-25,1,0
9780156006248,The History of the Siege of Lisbon,Jose Saramago,1998-01-21,2,0
9780156007757,Blindness,Jose Saramago,1999-06-26,6,0
9780156010597,All the Names,Jose Saramago,2001-07-27,2,0
9780156013031,The Tale of the Unknown Island,Jose Saramago,2000-02-22,3,0
9780156028790,The Cave,Jose Saramago,2003-03-23,5,0
9781860465024,The Year of the Death of Ricardo Reis,Jose Saramago,1998-04-24,4,0
9780192801739,Typhoon and Other Tales,Joseph Conrad,2002-08-28,3,0
9781551111728,Lord Jim,Joseph Conrad,2000-09-29,5,0
9780099477310,Catch22,Joseph Heller,1994-10-30,4,0
9780684839745,Good as Gold,Joseph Heller,1997-11-31,1,0
9780684841212,Something Happened,Joseph Heller,1974-12-01,6,0
9780684841250,God Knows,Joseph Heller,1997-01-02,2,0
9780684868196,Picture This,Joseph Heller,2000-02-03,3,0
9780316066143,Hollywood Station,Joseph Wambaugh,2006-03-04,5,0
9780440164173,The New Centurions,Joseph Wambaugh,1987-04-05,4,0
9780553273861,The Delta Star,Joseph Wambaugh,1984-05-06,1,0
9780553575958,Floaters,Joseph Wambaugh,1997-06-07,6,0
9780374253844,That Same Flower,Jostein Gaarder,1998-10-11,4,0
9780374530716,Sophies World,Jostein Gaarder,2007-07-08,2,0
9780753811467,Maya,Jostein Gaarder,2001-08-09,3,0
9780753819920,The Orange Girl,Jostein Gaarder,2005-09-10,5,0
9780312354077,Dirty Little Secrets,Joy King,2006-11-12,1,0
9780385468862,Obasan,Joy Kogawa,1994-12-13,6,0
9780060816223,Missing Mom,Joyce Carol Oates,2006-01-14,2,0
9780156030274,The Female of the Species,Joyce Carol Oates,2007-02-15,3,0
9780345484406,Them,Joyce Carol Oates,2006-03-16,5,0
9780452275003,Zombie,Joyce Carol Oates,1996-05-18,1,0
9780452277243,Man Crazy,Joyce Carol Oates,1998-06-19,6,0
9780452282827,We Were the Mulvaneys,Joyce Carol Oates,1996-07-20,2,0
9780786712946,Rape,Joyce Carol Oates,2003-08-21,3,0
9780786714827,Rape,Joyce Carol Oates,2004-09-22,5,0
9780812976557,Wonderland,Joyce Carol Oates,2006-10-23,4,0
9780880014403,The Assignation,Joyce Carol Oates,1996-11-24,1,0
9780880015080,First Love,Joyce Carol Oates,1997-12-25,6,0
9780805077810,The Nubian Prince,Juan Bonilla,2006-01-26,2,0
9780292701328,Paso Del Norte,Juan Rulfo,1967-02-27,3,0
9780618258024,The Lord of the Rings,Jude Fisher,2002-03-28,5,0
9780618510825,The Lord of the Rings Complete Visual Companion,Jude Fisher,2004-04-29,4,0
9780756401108,Sorcery Rising,Jude Fisher,2003-05-30,1,0
9780821758267,A Devilish Dilemma,Judith Lansdowne,1998-6-31,6,0
9780743474160,Paradise,Judith McNaught,2003-07-01,2,0
9780451529770,Around the World in Eighty Days,Jules Verne,2005-08-02,3,0
9780553213973,Journey To The Center Of The Earth,Jules Verne,2006-09-03,5,0
9781410103277,The End of Nana Sahib,Jules Verne,2003-10-04,4,0
9781405228183,Den of Thieves,Julia Golding,2007-12-12,6,0
9780679731375,A History of the World in 10 12 Chapters,Julian Barnes,1990-12-06,6,0
9781400097036,Arthur and George,Julian Barnes,2007-01-07,2,0
9780441012114,Conquerors Moon,Julian May,2005-02-08,3,0
9780756403454,Regeneration,Julie E. Czerneda,2006-03-09,5,0
9780345453860,Shadow Dance,Julie Garwood,2007-04-10,4,0
9780373792733,The Perfect Score,Julie Kenner,2006-05-11,1,0
9780505524744,Aphrodites Passion,Julie Kenner,2002-06-12,6,0
9780743496148,The Manolo Matrix,Julie Kenner,2006-07-13,2,0
9781416501626,Dirty Little Secrets,Julie Leto,2005-08-14,3,0
9780765309969,Blade of Fortriu,Juliet Marillier,2006-09-15,5,0
9780765309983,The Dark Mirror,Juliet Marillier,2006-10-16,4,0
9780765345905,Wolfskin,Juliet Marillier,2004-11-17,1,0
9781857024074,A Thousand Orange Trees,Kathryn Harrison,1995-06-21,6,0
9780439405584,The Journey,Kathryn Lasky,2003-05-25,1,0
9780439405591,The Rescue,Kathryn Lasky,2004-06-26,6,0
9780439884761,Guardians of Gahoole,Kathryn Lasky,2006-07-27,2,0
9780451207142,The pillars of the earth,Ken Follett,2002-12-18,6,0
9780451207524,Jackdaws,Ken Follett,2002-01-19,2,0
9780451207791,The Key to Rebecca,Ken Follett,2003-02-20,3,0
9780451208705,The Man from St. Petersburg,Ken Follett,2003-03-21,5,0
9780451211477,Night Over Water,Ken Follett,2004-04-22,4,0
9780140139976,Sailor Song,Ken Kesey,1993-05-23,1,0
9780143039860,Sometimes a Great Notion,Ken Kesey,1964-06-24,6,0
9780688143886,Julius the Baby of the World,Kevin Henkes,1995-08-28,3,0
9780688154721,Chesters Way,Kevin Henkes,1997-09-29,5,0
9780802789471,Once Upon a Cool Motorcycle Dude,Kevin OMalley,2005-10-30,4,0
9781933633107,Sister Bernadettes Barking Dog,Kitty Burns Florey,2006-06-29,6,0
9780439440035,Hope Springs Eternal,Kristiana Gregory,2005-11-31,1,0
9780751504354,Red Phoenix,Larry Bond,1992-01-13,2,0
9780152057640,Beauty Shop for Rent,Laura Bowers,2007-12-01,6,0
9780060885373,Little House in the Big Woods,Laura Ingalls Wilder,2007-01-02,2,0
9780060885380,Farmer Boy,Laura Ingalls Wilder,2006-02-03,3,0
9780060885427,The Long Winter,Laura Ingalls Wilder,2007-03-04,5,0
9780060885434,Little Town on the Prairie,Laura Ingalls Wilder,2007-04-05,4,0
9780060885458,The First Four Years,Laura Ingalls Wilder,2007-05-06,1,0
9780064406925,Winter on the Farm,Laura Ingalls Wilder,1997-06-07,6,0
9780064420815,Christmas Stories,Laura Ingalls Wilder,1998-07-08,2,0
9780064433730,Winter Days in the Big Woods,Laura Ingalls Wilder,1995-08-09,3,0
9780064434874,Christmas in the Big Woods,Laura Ingalls Wilder,1997-09-10,5,0
9780064434942,A Little House Birthday,Laura Ingalls Wilder,1998-10-11,4,0
9780064434980,The Deer in the Wood,Laura Ingalls Wilder,1999-11-12,1,0
9780064435260,A Little Prairie House,Laura Ingalls Wilder,1999-12-13,6,0
9780590488129,These Happy Golden Years,Laura Ingalls Wilder,1953-02-14,3,0
9780152049676,Winter is the Warmest Season,Lauren Stringer,2006-01-14,2,0
9780064403368,Child of the Owl,Laurence Yep,1990-02-15,3,0
9780064404419,The Rainbow People,Laurence Yep,1992-03-16,5,0
9780064404891,Dragons Gate,Laurence Yep,1995-04-17,4,0
9780064406031,American Dragons,Laurence Yep,1995-05-18,1,0
9780810957800,Babars World Tour,Laurent de Brunhoff,2005-06-19,6,0
9781584850458,Homeless,Laurie Halse Anderson,2000-07-20,2,0
9781584850557,Teachers Pet,Laurie Halse Anderson,2001-08-21,3,0
9780752834528,The Sins of the Fathers,Lawrence Block,2000-01-18,2,0
9780439291491,Alice in Wonderland,Lewis Carroll,2002-09-22,5,0
9781551112237,Alices Adventures in Wonderland,Lewis Carroll,2000-10-23,4,0
9780141310688,Westmark,Lloyd Alexander,2002-11-24,1,0
9780141310695,The Kestrel,Lloyd Alexander,2002-12-25,6,0
9780142301449,The Philadelphia Adventure,Lloyd Alexander,2002-01-26,2,0
9780525467779,Three Complete Novels,Lloyd Alexander,2001-02-27,3,0
9780805080490,The Black Cauldron,Lloyd Alexander,2006-03-28,5,0
9780805080513,Taran Wanderer,Lloyd Alexander,2006-04-29,4,0
9780805080520,The High King,Lloyd Alexander,2006-05-30,1,0
9780805080537,The Foundling,Lloyd Alexander,2006-6-31,6,0
9780064405850,Strawberry Girl 60th Anniversary Edition,Lois Lenski,1995-07-01,2,0
9780375827488,The Easter Rabbits Parade,Lois Lenski,2004-08-02,3,0
9780385732536,Messenger,Lois Lowry,2004-09-03,5,0
9780385732550,The Giver,Lois Lowry,2006-10-04,4,0
9780385732567,Gathering Blue,Lois Lowry,2006-11-05,1,0
9780440227533,Number the Stars,Lois Lowry,1989-12-06,6,0
9780440402916,Anastasia on Her Own,Lois Lowry,1985-01-07,2,0
9780440414001,See You Around Sam!,Lois Lowry,1998-02-08,3,0
9780440415244,Stay!,Lois Lowry,1999-03-09,5,0
9780440419808,The Silent Boy,Lois Lowry,2005-04-10,4,0
9780618685509,Gossamer,Lois Lowry,2006-05-11,1,0
9781400033829,Who Will Run the Frog Hospital?,Lorrie Moore,2004-06-12,6,0
9780380731503,Wayside School Is Falling Down (rack),Louis Sachar,1998-07-13,2,0
9780060004507,An OldFashioned Thanksgiving,Louisa May Alcott,2005-08-14,3,0
9780688151324,Behind a Mask,Louisa May Alcott,1997-07-25,2,0
9780813516707,Moods,Louisa May Alcott,1991-08-26,3,0
9781562926168,The Quiet Little Woman,Louisa May Alcott,1999-10-28,4,0
9780448400631,Anne of Avonlea,Lucy Maud Montgomery,1990-09-15,5,0
9780553560688,The Road to Yesterday,Lucy Maud Montgomery,1993-10-16,4,0
9780385490818,The Handmaids Tale,Margaret Atwood,1998-11-29,1,0
9780385491037,The Robber Bride,Margaret Atwood,1998-12-30,6,0
9780385491051,Surfacing,Margaret Atwood,1998-01-31,2,0
9780385491082,Lady Oracle,Margaret Atwood,1998-02-01,3,0
9780385503846,Moral Disorder,Margaret Atwood,2006-03-02,5,0
9780385721677,Oryx and Crake,Margaret Atwood,2004-04-03,4,0
9780786717675,Writing with Intent,Margaret Atwood,2006-07-30,2,0
9781841957173,The Penelopiad,Margaret Atwood,2005-05-04,1,0
9780312155858,Mary Queen of Scotland & The Isles,Margaret George,1997-06-05,6,0
9780312194390,The Autobiography of Henry VIII,Margaret George,1998-07-06,2,0
9780670037780,Helen of Troy,Margaret George,2006-08-07,3,0
9780449001967,Murder in Foggy Bottom,Margaret Truman,2002-09-08,5,0
9780449007389,Murder at Fords Theatre,Margaret Truman,2003-10-09,4,0
9780553271645,Doom of the Darksword,Margaret Weis,1988-11-10,1,0
9780553563696,The Hand of Chaos,Margaret Weis,1993-12-11,6,0
9780786913145,The Soulforge,Margaret Weis,1999-01-12,2,0
9780786931934,The Search for Power,Margaret Weis,2004-02-13,3,0
9780786937424,Amber and Ashes,Margaret Weis,2005-03-14,5,0
9780886778873,New Amazons,Margaret Weis,2000-04-15,4,0
9780394743042,The Ravishing of Lol Stein,Marguerite Duras,1986-05-16,1,0
9780802130365,The Malady of Death,Marguerite Duras,1988-06-17,6,0
9780802151544,Destroy She Said,Marguerite Duras,1986-07-18,2,0
9780374529260,Memoirs of Hadrian,Marguerite Yourcenar,2005-08-19,3,0
9780060090371,Lucy Sullivan Is Getting Married,Marian Keyes,2002-09-20,5,0
9780060731304,Anybody Out There?,Marian Keyes,2006-10-21,4,0
9780060787035,Cracks in My Foundation,Marian Keyes,2005-11-22,1,0
9780099489986,Watermelon,Marian Keyes,2005-12-23,6,0
9780140271799,Rachels Holiday,Marian Keyes,1997-01-24,2,0
9780141007472,Under The Duvet,Marian Keyes,2002-02-25,3,0
9780373274611,The Bluest Eyes in Texas,Marilyn Pappano,2005-03-26,5,0
9780002005883,Gilead,Marilynne Robinson,2004-04-27,4,0
9780345432407,Omerta,Mario Puzo,2001-05-28,1,0
9780345441690,The Dark Arena,Mario Puzo,2001-06-29,6,0
9780345441706,The Sicilian,Mario Puzo,2001-07-30,2,0
9780451160195,Fools Die,Mario Puzo,1979-08-31,3,0
9780451217400,The Godfather,Mario Puzo,2005-09-01,5,0
9780451454249,The Forest House,Marion Zimmer Bradley,1995-10-02,4,0
9780670037773,Special Topics in Calamity Physics,Marisha Pessl,2006-11-03,1,0
9780737000368,The Greenlander,Mark Adlard,1978-03-15,5,0
9780349113005,Embrace,Mark Behr,2001-12-04,6,0
9780385722438,Ella Minnow Pea,Mark Dunn,2001-01-05,2,0
9781400032716,The curious incident of the dog in the nighttime,Mark Haddon,2003-02-06,3,0
9780345448194,Boogaloo on 2nd Avenue,Mark Kurlansky,2005-03-07,5,0
9780306809576,Sammlung,Mark Twain,2000-08-31,3,0
9780393020397,The Annotated Huckleberry Finn,Mark Twain,2001-04-08,4,0
9780553211955,The Complete Short Stories of Mark Twain,Mark Twain,2005-06-10,6,0
9780743436502,Roughing It,Mark Twain,2003-07-11,2,0
9780764587276,CliffsComplete The Adventures of Huckleberry Finn,Mark Twain,2001-08-12,3,0
9781402714603,The Adventures of Tom Sawyer,Mark Twain,2004-11-17,1,0
9781402726002,The Adventures of Huckleberry Finn,Mark Twain,2006-12-18,6,0
9781416520382,Happy Hour at Casa Dracula,Marta Acosta,2006-09-13,5,0
9781416520399,Midnight Brunch,Marta Acosta,2007-10-14,4,0
9780451219442,Belle Ruin,Martha Grimes,2006-11-15,1,0
9780451220721,The Old Wine Shades,Martha Grimes,2007-12-16,6,0
9780451411617,Jerusalem Inn,Martha Grimes,2004-01-17,2,0
9780670037865,Dust,Martha Grimes,2007-02-18,3,0
9780679734482,Success,Martin Amis,1991-03-19,5,0
9780679734499,Dead Babies,Martin Amis,1975-04-20,4,0
9781400077274,Yellow Dog,Martin Amis,2005-05-21,1,0
9781933368368,The Good Fairies of New York,Martin Millar,2006-06-22,6,0
9780778322948,The Beach House,Mary Alice Monroe,2006-07-23,2,0
9781590583425,Effigies,Mary Anna Evans,2011-08-24,3,0
9780440241058,Slightly Wicked,Mary Balogh,2003-09-25,5,0
9780440243069,The Gilded Web,Mary Balogh,2006-10-26,4,0
9780373274482,In Dark Waters,Mary Burton,2005-11-27,1,0
9780449004135,A Thread of Grace,Mary Doria Russell,2005-12-28,6,0
9780449004838,Children of God,Mary Doria Russell,1999-01-29,2,0
9780684843124,Two Girls Fat and Thin,Mary Gaitskill,1998-2-30,3,0
9780671004545,You Belong To Me,Mary Higgins Clark,1999-03-31,5,0
9780671014919,My Gal Sunday,Mary Higgins Clark,2003-04-01,4,0
9780671027124,All Through the Night,Mary Higgins Clark,1999-05-02,1,0
9780671519186,The Night Awakens,Mary Higgins Clark,2000-06-03,6,0
9780743264914,I Heard that Song Before,Mary Higgins Clark,2007-07-04,2,0
9780743412629,The Second Time Around,Mary Higgins Clark,2004-08-05,3,0
9780743418133,Deck the Halls,Mary Higgins Clark,2001-10-07,4,0
9780743456869,He Sees You When Youre Sleeping,Mary Higgins Clark,2002-11-08,1,0
9781416507772,Where Are the Children?,Mary Higgins Clark,2005-09-06,5,0
9781416535522,Santa Cruise,Mary Higgins Clark,2006-12-09,6,0
9781894917124,The Devils in the Details,Mary Jane Maffini,2004-01-10,2,0
9780060519131,Savannah Blues,Mary Kay Andrews,2003-02-11,3,0
9780373288564,The Gunslinger,Mary McBride,1995-03-12,5,0
9780679890706,Earthquake in the Early Morning,Mary Pope Osborne,2001-01-19,2,0
9780786809288,The Tales from the Odyssey #1: OneEyed Giant,Mary Pope Osborne,2003-02-20,3,0
9780786809301,Sirens and Sea Monsters,Mary Pope Osborne,2003-04-22,4,0
9780786809943,The Final Battle,Mary Pope Osborne,2005-05-23,1,0
9780743487580,Frankenstein,Mary Shelley,2004-04-13,4,0
9780060502959,Moonspinners,Mary Stewart,2003-05-14,1,0
9780060548285,The Wicked Day,Mary Stewart,2003-06-15,6,0
9780060747473,This Rough Magic,Mary Stewart,2004-07-16,2,0
9780060747480,Airs Above the Ground,Mary Stewart,2004-08-17,3,0
9780060823726,Touch Not the Cat,Mary Stewart,2005-09-18,5,0
9780061145391,The Gabriel Hounds,Mary Stewart,2006-10-19,4,0
9780688003470,The Merlin Trilogy,Mary Stewart,1980-11-20,1,0
9780099556312,Airframe,Michael Crichton,1997-04-16,4,0
9780140178975,Essays,Michel de Montaigne,1993-09-01,5,0
9780140446043,The Complete Essays,Michel Montaigne,2004-10-02,4,0
9780060841867,The Curtain,Milan Kundera,2006-11-03,1,0
9780060927516,Testaments Betrayed,Milan Kundera,1996-12-04,6,0
9780156003650,The Double Flame,Octavio Paz,1996-01-05,2,0
9780061093982,Treasure Box,Orson Scott Card,1997-12-21,6,0
9780061093999,Homebody,Orson Scott Card,1999-01-22,2,0
9780312861872,Xenocide,Orson Scott Card,1996-02-23,3,0
9780312876623,Songmaster,Orson Scott Card,2002-03-24,5,0
9780345482402,Enchantment,Orson Scott Card,2005-04-25,4,0
9780765304742,Children of the Mind,Orson Scott Card,2002-05-26,1,0
9780765309044,Treason,Orson Scott Card,2006-06-27,6,0
9780765316110,Empire,Orson Scott Card,2006-07-28,2,0
9780765341174,Sarah,Orson Scott Card,2001-08-29,3,0
9780765341280,Rebekah,Orson Scott Card,2002-09-30,5,0
9780765341297,Rachel & Leah,Orson Scott Card,2005-10-31,4,0
9780812508642,Pastwatch,Orson Scott Card,1997-11-01,1,0
9780812521351,Harts Hope,Orson Scott Card,1988-12-02,6,0
9780812524260,Red Prophet,Orson Scott Card,1988-01-03,2,0
9780812532616,The Call of Earth,Orson Scott Card,1994-02-04,3,0
9780812532630,The Ships of Earth,Orson Scott Card,1995-03-05,5,0
9780812565959,Shadow of the Hegemon,Orson Scott Card,2001-04-06,4,0
9781573456630,Stone Tables,Orson Scott Card,2000-05-07,1,0
9780140430899,De Profundis and Other Writings,Oscar Wilde,1973-06-08,6,0
9780192807298,The Picture of Dorian Gray,Oscar Wilde,2006-07-09,2,0
9780192833761,Complete Shorter Fiction,Oscar Wilde,1998-08-10,3,0
9780375751516,The Picture of Dorian Gray,Oscar Wilde,1998-09-11,5,0
9780486419251,The Canterville Ghost and Other Stories,Oscar Wilde,2001-10-12,4,0
9781557424297,The Picture of Dorian Gray,Oscar Wilde,2005-11-13,1,0
9781592241873,The Canterville Ghost,Oscar Wilde,2005-12-14,6,0
9781595690364,Teleny Or The Reverse of the Medal,Oscar Wilde,2006-01-15,2,0
9780006499268,The Reverse of the Medal,Patrick OBrian,1997-05-17,1,0
9780140097313,The New York Trilogy,Paul Auster,1987-02-28,3,0
9780140115857,Moon Palace,Paul Auster,1989-02-16,3,0
9780140154078,The Music of Chance,Paul Auster,1991-03-17,5,0
9780140178135,Leviathan,Paul Auster,1993-04-18,4,0
9780312263997,Timbuktu,Paul Auster,1999-05-19,1,0
9780312424688,Collected Prose,Paul Auster,2005-02-06,3,0
9780312426231,The Brooklyn Follies,Paul Auster,2006-06-20,6,0
9780805081459,Travels in the Scriptorium,Paul Auster,2007-07-21,2,0
9780811214988,The Red Notebook,Paul Auster,2002-08-22,3,0
9783425040844,In the Country of Last Things,Paul Auster,2001-03-29,5,0
9780060834821,The Sheltering Sky,Paul Bowles,2005-09-23,5,0
9780061137037,Spiders House,Paul Bowles,2006-10-24,4,0
9780061137365,Days,Paul Bowles,2006-11-25,1,0
9780061139635,Points in Time,Paul Bowles,2006-12-26,6,0
9780060527983,Warrior of the Light,Paulo Coelho,2004-01-27,2,0
9780060527990,The Devil and Miss Prym,Paulo Coelho,2006-02-28,3,0
9780060589288,Eleven Minutes,Paulo Coelho,2005-03-29,5,0
9780060887964,The Alchemist  Gift Edition,Paulo Coelho,2006-04-30,4,0
9780060930134,The Fifth Mountain,Paulo Coelho,1999-05-31,1,0
9780061122095,By the River Piedra I Sat Down and Wept,Paulo Coelho,2006-06-01,6,0
9780061122415,The Alchemist,Paulo Coelho,2006-07-02,2,0
9780061124266,Veronika Decides to Die,Paulo Coelho,2006-08-03,3,0
9780062513342,The Valkyries,Paulo Coelho,1996-09-04,5,0
9780747544210,Easy Riders Raging Bulls,Peter Biskind,1999-10-13,4,0
9780345253590,The best of Philip K. Dick,Philip K. Dick,1977-10-05,4,0
9780575076815,A Scanner Darkly,Philip K. Dick,2006-02-19,3,0
9780765316929,Voices From the Street,Philip K. Dick,2007-11-06,1,0
9780806521688,The Minority Report,Philip K. Dick,1999-12-07,6,0
9780806523798,The Minority Report,Philip K. Dick,2002-01-08,2,0
9781400030064,The Crack in Space,Philip K. Dick,1966-02-09,3,0
9781400030088,Lies Inc,Philip K. Dick,2004-03-10,5,0
9781400030125,Vulcans Hammer,Philip K. Dick,1960-04-11,4,0
9780440238607,His Dark Materials,Philip Pullman,2003-05-12,1,0
9780375707216,I Married a Communist,Philip Roth,1999-06-13,6,0
9780679749066,The Great American Novel,Philip Roth,1973-07-14,2,0
9780679759256,When She was Good,Philip Roth,1995-08-15,3,0
9780679764175,Letting Go,Philip Roth,1997-09-16,5,0
9781400079490,The Plot Against America,Philip Roth,2005-10-17,4,0
9780618586455,The Best American Spiritual Writing 2006,Philip Zaleski,2006-03-07,5,0
9780449146972,The Changeling,Philippa Carr,1990-11-18,1,0
9780743227445,The Other Boleyn Girl,Philippa Gregory,2001-12-19,6,0
9780743249294,Wideacre,Philippa Gregory,2003-01-20,2,0
9780743249300,The Favored Child,Philippa Gregory,2003-02-21,3,0
9780743269261,The Virgins Lover,Philippa Gregory,2005-03-22,5,0
9780743272490,The Constant Princess,Philippa Gregory,2006-04-23,4,0
9780743272506,The Boleyn Inheritance,Philippa Gregory,2006-05-24,1,0
9780743272537,Virgin Earth,Philippa Gregory,2006-06-25,6,0
9780385423397,The Art of the Personal Essay,Phillip Lopate,1995-04-08,4,0
9780385497145,Waterfront,Phillip Lopate,2005-05-09,1,0
9780099742005,Total Recall,Piers Anthony,1990-07-26,2,0
9780345305183,On a pale horse,Piers Anthony,1984-08-27,3,0
9780380004614,Ox,Piers Anthony,1976-09-28,5,0
9780380017799,Chaining the Lady,Piers Anthony,1978-10-29,4,0
9780380759507,Firefly,Piers Anthony,1992-11-30,1,0
9780441317486,Hard Sell,Piers Anthony,1993-12-31,6,0
9780441444250,Killobyte,Piers Anthony,1994-01-01,2,0
9780441731183,Robot Adept,Piers Anthony,1989-02-02,3,0
9780441864614,Vision of Tarot,Piers Anthony,1987-03-03,5,0
9780765304094,Stork Naked,Piers Anthony,2006-04-04,4,0
9780765343116,Pet Peeve,Piers Anthony,2006-05-05,1,0
9780812531145,Anthonology,Piers Anthony,1986-06-06,6,0
9780812534832,Demons Dont Dream,Piers Anthony,1994-07-07,2,0
9780812534863,Roc and a Hard Place,Piers Anthony,1996-08-08,3,0
9780812555103,Yon Ill Wind,Piers Anthony,1997-09-09,5,0
9780812574739,The Dastard,Piers Anthony,2001-10-10,4,0
9780812574746,Swell Foop,Piers Anthony,2002-11-11,1,0
9780812574968,Vale of the Vole,Piers Anthony,2000-12-12,6,0
9780812574999,Up In a Heaval,Piers Anthony,2003-01-13,2,0
9780486427591,Gorgias and Timaeus,Plato,2003-06-10,6,0
9781883011079,Raymond Chandler: Stories & Early Novels,Raymond Chandler,1995-06-23,6,0
9780586217832,Magician,Raymond E. Feist,1993-06-18,6,0
9780099427865,Illusions,Richard Bach,2001-07-19,2,0
9780940450660,Richard Wright,Richard Wright,1991-07-11,2,0
9780140320435,Charlie and the Great Glass Elevator,Roald Dahl,1986-08-20,3,0
9780141310343,Skin and Other Stories,Roald Dahl,2002-06-24,6,0
9780141311357,James and the Giant Peach,Roald Dahl,2001-09-21,5,0
9780142404201,Charlie and the Chocolate Factory,Roald Dahl,2005-07-25,2,0
9780670036653,The Roald Dahl Treasury,Roald Dahl,2003-08-26,3,0
9780140307375,Little Plum,Rumer Godden,1987-02-01,3,0
9780440987901,Thursdays Children,Rumer Godden,1987-03-02,5,0
9781590171240,An Episode of Sparrows,Rumer Godden,2004-04-03,4,0
9780718149291,Medicus and the Disappearing Dancing Girls,Ruth Downie,2006-03-20,5,0
9780312183011,Radio On,Sarah Vowell,1997-08-12,3,0
9780231073370,The Pillow Book of Sei Sh?nagon,Sei Shōnagon,1991-09-13,5,0
9780006472612,Master of the Game,Sidney Sheldon,1982-10-22,4,0
9780006479673,If Tomorrow Comes,Sidney Sheldon,1994-11-23,1,0
9780195144819,El Libertador,Simón Bolívar,2003-10-14,4,0
9780552998871,The Secret Dreamworld of a Shopaholic,Sophie Kinsella,2000-01-16,2,0
9780140443073,Love,Stendhal,1975-11-15,1,0
9780393927207,The Norton Anthology of English Literature,Stephen Greenblatt,2006-12-16,6,0
9780340829776,The Waste Lands,Stephen King,2003-02-02,3,0
9780385129916,Night Shift,Stephen King,1978-02-14,3,0
9780425181607,Stephen Kings Danse Macabre,Stephen King,2001-03-15,5,0
9780451150653,Salems Lot,Stephen King,1976-04-16,4,0
9780451155757,The Dead Zone,Stephen King,1980-05-17,1,0
9780451160522,The Gunslinger,Stephen King,1982-06-18,6,0
9780451161352,Cujo,Stephen King,1982-07-19,2,0
9780451166586,The Eyes of the Dragon,Stephen King,1988-08-20,3,0
9780451168610,Skeleton Crew,Stephen King,1986-09-21,5,0
9780451169518,It,Stephen King,1990-10-22,4,0
9780451170118,Night Shift,Stephen King,1978-11-23,1,0
9780451173317,The Waste Lands,Stephen King,1993-12-24,6,0
9780451210852,The Drawing of the Three,Stephen King,2003-01-25,2,0
9780453005074,The Bachman Books,Stephen King,1977-02-26,3,0
9780517219027,Three complete novels,Stephen King,2002-03-27,5,0
9780671024239,Bag of Bones,Stephen King,1999-04-28,4,0
9780671039721,Carrie,Stephen King,2002-05-29,1,0
9780671039745,Salems Lot,Stephen King,1999-06-30,6,0
9780671042851,The Girl Who Loved Tom Gordon,Stephen King,1999-07-31,2,0
9780743289412,Liseys Story,Stephen King,2006-08-01,3,0
9780743437493,The Shining,Stephen King,2002-09-02,5,0
9780896214408,Rita Hayworth and Shawshank Redemption,Stephen King,1982-10-03,4,0
9780905712604,The Shining,Stephen King,1987-11-04,1,0
9780965796934,Storm of the century,Stephen King,1999-12-05,6,0
9781416524519,Cell,Stephen King,2006-01-06,2,0
9781587671401,The Secretary of Dreams,Stephen King,2006-02-07,3,0
9781594860164,Live Rich Die Broke,Stephen M. Pollan,2004-02-17,3,0
9781594481949,Everything Bad is Good for You,Steven Johnson,2006-12-02,6,0
9780142003343,The Blank Slate,Steven Pinker,2003-01-03,2,0
9780701179793,The Risk of Darkness,Susan Hill,2006-04-21,4,0
9780345487421,Feel the Fear and Do it Anyway,Susan J. Jeffers,2007-02-04,3,0
9780192833006,Agricola and Germany,Tacitus,1999-01-17,2,0
9780465017744,After Theory,Terry Eagleton,2004-02-18,3,0
9781850522317,Red Dragon,Thomas Harris,1992-12-24,6,0
9780060925758,Soul Mates,Thomas Moore,1994-03-05,5,0
9780375507151,Cliffs of Despair,Tom Hunt,2006-04-06,4,0
9780674673779,Playing in the Dark,Toni Morrison,1992-10-19,4,0
9780679745570,The grass harp,Truman Capote,1993-03-08,5,0
9780679745648,Other Voices Other Rooms,Truman Capote,1994-04-09,4,0
9780812975932,Summer Crossing,Truman Capote,2006-06-11,6,0
9781400096916,The Complete Stories of Truman Capote,Truman Capote,2005-05-10,1,0
9780156029063,Baudolino,Umberto Eco,2003-07-12,2,0
9780156032391,On Literature,Umberto Eco,2005-03-19,5,0
9780156032971,Foucaults Pendulum,Umberto Eco,2007-08-13,3,0
9780156913218,Travels in Hyper Reality,Umberto Eco,1990-04-20,4,0
9780253202178,A Theory of Semiotics,Umberto Eco,1979-11-20,1,0
9780253203182,The Role of the Reader,Umberto Eco,1984-12-21,6,0
9780307264893,The Name of the Rose,Umberto Eco,2006-09-14,5,0
9780330334686,Misreadings,Umberto Eco,1994-01-22,2,0
9780553383041,A Wizard of Earthsea,Ursula K. Le Guin,2004-10-15,4,0
9780689845369,The Tombs of Atuan,Ursula K. Le Guin,2001-11-16,1,0
9781416509646,The Farthest Shore,Ursula K. Le Guin,2004-12-17,6,0
9781590300060,The Wave in the Mind,Ursula K. Le Guin,2004-05-21,1,0
9780671039943,Ice,V. C. Andrews,2001-01-18,2,0
9780743428675,Black Cat,V. C. Andrews,2004-02-19,3,0
9780330487146,A Bend in the River,V. S. Naipaul,2002-03-20,5,0
9780671007638,Runaways,V.C. Andrews,1998-04-21,4,0
9780743449021,Shooting Stars Omnibus,V.C. Andrews,2002-05-22,1,0
9780373028603,The Love Artist,Valerie Parv,1987-06-23,6,0
9780373033669,P.S. I Love You,Valerie Parv,1995-07-24,2,0
9780812538830,Seminole Song,Vella Munn,1998-08-25,3,0
9780195108965,Notebooks of the Mind,Vera John Steiner,1997-05-07,1,0
9780451525260,Les Miserables a New Unabridged Translation,Victor Hugo,1987-09-26,5,0
9780807014264,Mans Search for Meaning,Viktor Emil Frankl,1992-06-08,6,0
9780393974294,The Norton Anthology of Theory and Criticism,Vincent B. Leitch,2001-02-23,3,0
9780140449327,The Aeneid,Virgil,2003-03-24,5,0
9780141182490,Mrs Dalloway,Virginia Woolf,2000-10-27,4,0
9780141183534,A Room of Ones Own,Virginia Woolf,2002-11-28,1,0
9780141185323,The Years,Virginia Woolf,2002-12-29,6,0
9780151009985,Mrs. Dalloway,Virginia Woolf,2002-01-30,2,0
9780156027786,The Common Reader,Virginia Woolf,1984-06-22,6,0
9780156028066,Women and Writing,Virginia Woolf,2003-04-25,4,0
9780156030472,To the Lighthouse,Virginia Woolf,1927-2-31,3,0
9780156118705,Between the Acts,Virginia Woolf,1969-03-01,5,0
9780156212502,The Complete Shorter Fiction of Virginia Woolf,Virginia Woolf,1989-04-02,4,0
9780156628709,Mrs. Dalloway,Virginia Woolf,1981-05-03,1,0
9780156907392,To the Lighthouse,Virginia Woolf,1981-06-04,6,0
9780156935906,The Virginia Woolf Reader,Virginia Woolf,1984-05-26,1,0
9780192839701,Mrs Dalloway,Virginia Woolf,2000-03-18,5,0
9781930464063,On Being Ill,Virginia Woolf,2002-07-23,2,0
9780679726098,Strong Opinions,Vladimir Vladimirovich Nabokov,1990-08-24,3,0
9780674022874,The Writer of Modern Life,Walter Benjamin,2006-06-27,6,0
9780807840894,Allusions in Ulysses,Weldon Thornton,1982-07-28,2,0
9780822205104,The Heidi Chronicles,Wendy Wasserstein,1990-08-29,3,0
9780312940669,When the Lion Feeds,Wilbur Smith,2006-07-05,2,0
9780312940683,A Sparrow Falls,Wilbur Smith,2007-08-06,3,0
9780312980382,Warlock,Wilbur Smith,2002-09-07,5,0
9780140436075,The Law and the Lady,Wilkie Collins,1998-10-08,4,0
9780141439617,The Woman in White,Wilkie Collins,2003-11-09,1,0
9780192833075,Miss Or Mrs?,Wilkie Collins,1999-12-10,6,0
9781551116440,The Woman in White,Wilkie Collins,2006-01-11,2,0
9780961472825,Graphic Storytelling,Will Eisner,1996-09-30,5,0
9780060525101,Happiness,Will Ferguson,2003-02-12,3,0
9780743487696,My Antonia,Willa Cather,2004-03-13,5,0
9780140422153,The Complete Poems,William Blake,1977-10-31,4,0
9780142437285,The Portable Faulkner,William Faulkner,2003-09-25,5,0
9780679600176,The Sound and the Fury,William Faulkner,1992-06-16,6,0
9780679732174,Go Down Moses,William Faulkner,1942-07-17,2,0
9780679732266,Light in August,William Faulkner,1985-08-18,3,0
9780679736530,The Hamlet,William Faulkner,1991-09-19,5,0
9780679748144,Sanctuary,William Faulkner,1993-10-20,4,0
9780140187076,J R,William Gaddis,1993-11-21,1,0
9780142437636,Agapē Agape,William Gaddis,2003-12-22,6,0
9780425198681,Pattern Recognition,William Gibson,2005-01-23,2,0
9780441012039,Neuromancer,William Gibson,2004-02-24,3,0
9780441013678,Count Zero,William Gibson,2006-03-25,5,0
9780140283334,Lord of the Flies,William Golding,1999-04-26,4,0
9780156443791,The Inheritors,William Golding,1962-05-27,1,0
9780399529207,Lord of the Flies,William Golding,2003-06-28,6,0
9780812416114,Lord of the Flies,William Golding,1959-07-29,2,0
9781405835640,Spire,William Golding,2006-08-30,3,0
9780345418265,The Princess Bride,William Goldman,2003-9-31,5,0
9780345442635,The Silent Gondoliers,William Goldman,2001-10-01,4,0
9780440187356,Tinsel,William Goldman,1980-11-02,1,0
9780446300001,Heat,William Goldman,1986-12-03,6,0
9781933618081,Falling Angel,William Hjortsberg,2006-01-04,2,0
9780674705593,The Principles of Psychology,William James,1981-07-09,2,0
9780940450387,Writings 19021910,William James,1987-10-26,4,0
9781929241637,Beloved Bride,William Potter,2002-11-27,1,0
9780198320210,A Midsummer Nights Dream,William Shakespeare,2001-05-04,1,0
9780198320272,Julius Caesar,William Shakespeare,2001-06-05,6,0
9780198320548,King Lear,William Shakespeare,2002-07-06,2,0
9780198321460,Macbeth,William Shakespeare,2004-08-07,3,0
9780198321477,Much Ado about Nothing,William Shakespeare,2004-09-08,5,0
9780521618748,Hamlet,William Shakespeare,2005-10-09,4,0
9781586638535,King Lear,William Shakespeare,2003-11-01,1,0
9780590317672,Run,William Sleator,1973-05-22,1,0
9780140276336,White Teeth,Zadie Smith,2001-02-05,3,0
9780140276343,The Autograph Man,Zadie Smith,2003-03-06,5,0
9780375703867,White Teeth,Zadie Smith,2000-04-07,4,0
9780375703874,The Autograph Man,Zadie Smith,2003-05-08,1,0
9780060916497,Tell My Horse,Zora Neale Hurston,1990-06-09,6,0
9780060916510,Jonahs Gourd Vine,Zora Neale Hurston,1990-07-10,2,0
9780060921712,The Complete Stories,Zora Neale Hurston,1996-08-11,3,0
9780061120060,Their Eyes Were Watching God,Zora Neale Hurston,2006-09-12,5,0
"""

# Procesar libros
libros = [line.strip().split(",") for line in libros_raw.strip().split("\n")]

# Crear diccionario autor -> id
autor_id = {}
id_counter = 1
for libro in libros:
    autor = libro[2]
    if autor not in autor_id:
        autor_id[autor] = id_counter
        id_counter += 1

# Crear lista libros con codigo de autor reemplazado y fecha desglosada
libros_cod_autor = []
for libro in libros:
    isbn, titulo, autor, fecha_str, cant, prestados = libro
    codigo_autor = autor_id[autor]
    dia, mes, anio = map(int, fecha_str.split("-"))
    libros_cod_autor.append((isbn, titulo, codigo_autor, int(cant), int(prestados), dia, mes, anio))

# Formatos para struct.pack:
# libros: 14s 50s i i i i i  -> isbn, titulo, id_autor, cantidad, dia, mes, anio
# autores: i 50s               -> id_autor, nombre

formato_libro = '14s50siiiiii'
formato_autor = 'i50s'

# Guardar libros.dat
with open("C:/Users/alvar/Documents/GitHub/elLibrito_Feliz2/elLibrito_Feliz/archivos/libros.dat", "wb") as f:
    for libro in libros_cod_autor:
        isbn_bytes = libro[0].encode('utf-8')[:13].ljust(14, b'\0')
        titulo_bytes = libro[1].encode('utf-8')[:50].ljust(50, b'\0')
        id_autor = libro[2]
        cantidad = libro[3]
        prestados = libro[4]
        dia = libro[5]
        mes = libro[6]
        anio = libro[7]

        registro = struct.pack(formato_libro, isbn_bytes, titulo_bytes, id_autor, cantidad,prestados, dia, mes, anio)
        f.write(registro)

# Guardar autores.dat
with open("C:/Users/alvar/Documents/GitHub/elLibrito_Feliz2/elLibrito_Feliz/archivos/autores.dat", "wb") as f:
    for autor, id_autor in autor_id.items():
        nombre_bytes = autor.encode('utf-8')[:50].ljust(50, b'\0')
        registro = struct.pack(formato_autor, id_autor, nombre_bytes)
        f.write(registro)

print("Archivos binarios libros.dat y autores.dat creados correctamente.")

